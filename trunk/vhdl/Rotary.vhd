-- Library declarations
--
-- Standard IEEE libraries
--
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
--
------------------------------------------------------------------------------------
--
--
entity Rotary_Debouncer is
    Port (        rotary_a : in std_logic;
                  rotary_b : in std_logic;
                       clk : in std_logic;
							  rst : in std_logic;
					  rot_out_a : out std_logic;
				     rot_out_b : out std_logic);
    end Rotary_Debouncer;
--
------------------------------------------------------------------------------------
--
-- Start of test architecture
--
architecture Behavioral of Rotary_Debouncer is
--
------------------------------------------------------------------------------------
--
-- Signals used to interface to rotary encoder
--
signal      rotary_a_in : std_logic;
signal      rotary_b_in : std_logic;
signal        rotary_in : std_logic_vector(1 downto 0);
signal        rotary_q1 : std_logic;
signal        rotary_q2 : std_logic;
signal  delay_rotary_q1 : std_logic;
signal     rotary_event : std_logic;
signal      rotary_left : std_logic;
signal     rotary_a_out : std_logic;
signal     rotary_b_out : std_logic;
signal    	start_count : std_logic;
signal    	  end_count : std_logic;
signal				  cnt : std_logic_vector(20 downto 0);	




type rotary_state is (s0, s1, s2);
signal etat, nextetat: rotary_state;
------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--
-- Start of circuit description
--
begin
  --
  ----------------------------------------------------------------------------------------------------------------------------------
  -- Interface to rotary encoder.
  -- Detection of movement and direction.
  ----------------------------------------------------------------------------------------------------------------------------------
  --
  -- The rotary switch contacts are filtered using their offset (one-hot) style to  
  -- clean them. Circuit concept by Peter Alfke.
  -- Note that the clock rate is fast compared with the switch rate.

  rotary_filter: process(clk)
  begin
    if clk'event and clk='1' then

      --Synchronise inputs to clock domain using flip-flops in input/output blocks.
      rotary_a_in <= rotary_a;
      rotary_b_in <= rotary_b;
      
      --concatinate rotary input signals to form vector for case construct.
      rotary_in <= rotary_b_in & rotary_a_in;

      case rotary_in is

        when "00" => rotary_q1 <= '0';         
                     rotary_q2 <= rotary_q2;
 
        when "01" => rotary_q1 <= rotary_q1;
                     rotary_q2 <= '0';

        when "10" => rotary_q1 <= rotary_q1;
                     rotary_q2 <= '1';

        when "11" => rotary_q1 <= '1';
                     rotary_q2 <= rotary_q2; 

        when others => rotary_q1 <= rotary_q1; 
                       rotary_q2 <= rotary_q2; 
      end case;

    end if;
  end process rotary_filter;
  --
  -- The rising edges of 'rotary_q1' indicate that a rotation has occurred and the 
  -- state of 'rotary_q2' at that time will indicate the direction. 
  --
  direction: process(clk,start_count)
  begin
    if clk'event and clk='1' then

      delay_rotary_q1 <= rotary_q1;
      if rotary_q1='1' and delay_rotary_q1='0' then
        rotary_event <= '1';
        rotary_left <= rotary_q2;
	   else
        rotary_event <= '0';
        rotary_left <= rotary_left;
      end if;
	 end if;
  end process direction;
-- 
--	counter:process(clk)
--	begin
--		if clk'event and clk='1' then
--			if start_count='1' then
--				end_count<='0';			
--				cnt<=cnt+1;
--				if rotary_left='1' then 
--					rotary_a_out<='1';
--					rotary_b_out<='1';
--				else
--					rotary_a_out<='0';
--					rotary_b_out<='1';
--				end if;
--				if cnt(20)='1' then 
--					end_count<='1';
--					rotary_b_out<='0';
--				end if;
--			end if;
--		end if;
--	end process;
--
--
-- 
----	rot_out_a<=rotary_left;
----	rot_out_b<=rotary_event;
--  output: process(clk,end_count)
--  begin
--   if clk'event and clk='1' then
--		if rotary_event='1' then
--        start_count<='1';
--		end if;
--		if end_count='1' then
--			start_count<='0';
--		end if;
--		rot_out_a<=rotary_a_out;
--		rot_out_b<=rotary_b_out;
--	end if;
--  end process;
--  
  
  




seq: process(clk, rst)
begin
	if rst='1' then etat <= s0;
	elsif clk'event and clk='1' then etat <= nextetat;
	end if;
end process;

combi: process (etat,rotary_left,rotary_event )
begin
	case etat is
		when s0 =>
			rot_out_a<='0';
			rot_out_b<='0';
			if rotary_event='1' then
				if rotary_left='1' then nextetat <= s1;       -- to the left
				elsif rotary_left='0' then nextetat <= s2;	 -- to the right
				end if;
			end if;
		when s1 =>
			rot_out_a<='1';
			rot_out_b<='1';
			cnt<=cnt+1;
			if cnt(20)='1' then
					nextetat <= s0;
					cnt<=(others=>'0');
			end if;
		when s2 =>
			rot_out_a<='0';
			rot_out_b<='1';
			cnt<=cnt+1;
			if cnt(20)='1' then
					nextetat <= s0;
					cnt<=(others=>'0');
			end if;
		when others =>
			null;
	end case;
end process;


end;
