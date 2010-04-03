--------------------------------------------------
-- De-bounce the push buttons.
-- Jon Turner - 1/2008
--
-- This circuit produces a debounced version of the
-- S3 board's push buttons. It does this by ignoring
-- all changes to btn that are not stable for at least
-- 2^20 clock ticks (about 20 ms with a 50 MHz clock).
--------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity Button_Debouncer is port(
	clk: in std_logic;
	btn: in std_logic_vector(3 downto 0);
	dBtn: out std_logic_vector(3 downto 0));
end Button_Debouncer;

architecture debArch of Button_Debouncer is
signal prevBtn: std_logic_vector(3 downto 0);
-- for simulation, make count 2 bits long, for S3, make it 20
signal count: std_logic_vector(19 downto 0);
begin
	process(clk) begin
		if rising_edge(clk) then
			prevBtn <= btn;
			if prevBtn /= btn then count <= (others => '1');
			elsif count /= (count'range => '0') then count <= count - 1;
			else dBtn <= btn;
			end if;
		end if;
	end process; 
end debArch;
