--------------------------------------------------------------------------------
-- Company:  Department of Computer Science, University of Texas at San Antonio
-- Engineer:  Chia-Tien Dan Lo (danlo@cs.utsa.edu)
--
-- Create Date:    11:01:23 08/20/06
-- Design Name:    
-- Module Name:    vgatest - behavioral
-- Project Name:   
-- Target Device:   Xilinx Spartan 3 xc3s200 on Didilent Spartan-3 Starter Kit Board
-- Tool versions: ISE 8.1.03i 
-- Description: This VGA test will draw a single color page and change color
--					 every one second. VGA resolution is 640x480 @25 MHZ 8 colors
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
-- Pin Assignment:
-- MET clk50_in loc = T9
-- NET red_out LOC=R12; 
-- NET green_out LOC=T12;
-- NET blue_out LOC=R11;
-- NET hs_out LOC=R9; 
-- NET vs_out LOC=T10; 
--------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity vga_ctrl is
  port(clk50_in  : in std_logic;
       red_in   : in std_logic;
       green_in : in std_logic;
       blue_in  : in std_logic;
       hs_in    : in std_logic;
       vs_in    : in std_logic;
		 red_out   : out std_logic;
       green_out : out std_logic;
       blue_out  : out std_logic;
       hs_out    : out std_logic;
       vs_out    : out std_logic);
end vga_ctrl;

architecture logic of vga_ctrl is

signal clk25              : std_logic;
signal hcounter : integer range 0 to 800;
signal vcounter   : integer range 0 to 521;
signal color: std_logic_vector(2 downto 0);
begin

-- generate a 25Mhz clock
process (clk50_in)
begin
  if clk50_in'event and clk50_in='1' then
    clk25 <= not clk25;
  end if;
end process;

-- change color every one second
p1: process (clk25)
	variable cnt: integer;
begin
	if clk25'event and clk25='1' then
		cnt := cnt + 1;
		if cnt = 25000000 then
			color(2) <= red_in;
			color(1) <= green_in;
			color(0) <= blue_in;
			cnt := 0;
		end if;
	end if;
end process;

p2: process (clk25, hcounter, vcounter)
	variable x: integer range 0 to 639;
	variable y: integer range 0 to 479;
begin
	-- hcounter counts from 0 to 799
	-- vcounter counts from 0 to 520
	-- x coordinate: 0 - 639 (x = hcounter - 144, i.e., hcounter -Tpw-Tbp)
	-- y coordinate: 0 - 479 (y = vcounter - 31, i.e., vcounter-Tpw-Tbp)
	x := hcounter - 144;
	y := vcounter - 31;
  	if clk25'event and clk25 = '1' then
 		-- To draw a pixel in (x0, y0), simply test if the ray trace to it
		-- and set its color to any value between 1 to 7. The following example simply sets 
		-- the whole display area to a single-color wash, which is changed every one 
		-- second. 	
	 	if x < 640 and y < 480 then
      	red_out <= color(0);
      	green_out <= color(1); 
      	blue_out <= color(2);
    	else
			-- if not traced, set it to "black" color
      	red_out <= '0';
      	green_out <= '0';
      	blue_out <= '0';
    	end if;
		-- Here is the timing for horizontal synchronization.
		-- (Refer to p. 24, Xilinx, Spartan-3 Starter Kit Board User Guide)
	 	-- Pulse width: Tpw = 96 cycles @ 25 MHz
	 	-- Back porch: Tbp = 48 cycles
		-- Display time: Tdisp = 640 cycles
	 	-- Front porch: Tfp = 16 cycles
		-- Sync pulse time (total cycles) Ts = 800 cycles

    	if hcounter > 0 and hcounter < 97 then
      	hs_out <= '0';
    	else
      	hs_out <= '1';
    	end if;
		-- Here is the timing for vertical synchronization.
		-- (Refer to p. 24, Xilinx, Spartan-3 Starter Kit Board User Guide)
	 	-- Pulse width: Tpw = 1600 cycles (2 lines) @ 25 MHz
	 	-- Back porch: Tbp = 23200 cycles (29 lines)
		-- Display time: Tdisp = 38400 cycles (480 lines)
	 	-- Front porch: Tfp = 8000 cycles (10 lines)
		-- Sync pulse time (total cycles) Ts = 416800 cycles (521 lines)
    	if vcounter > 0 and vcounter < 3 then
      	vs_out <= '0';
    	else
      	vs_out <= '1';
    	end if;
	 	-- horizontal counts from 0 to 799
    	hcounter <= hcounter+1;
    	if hcounter = 800 then
      	vcounter <= vcounter+1;
      	hcounter <= 0;
    	end if;
	 	-- vertical counts from 0 to 519
    	if vcounter = 521 then		    
      	vcounter <= 0;
    	end if;
  end if;
end process;

end;

