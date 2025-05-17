----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:39:05 05/17/2025 
-- Design Name: 
-- Module Name:    memory - mem 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity memory is
    Port ( address : in  integer;
           input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC);
end memory;

architecture mem of memory is

	SIGNAL state: STD_LOGIC_VECTOR(1919 downto 0);

begin
	setter: process(clk) begin
		if rising_edge(clk) then
			if set = '1' then
				state(address*8 + 7 downto address*8) <= input;
			end if;
		end if;
	end process setter;

	output(15 downto 8) <= state(address*8 + 7 downto address*8);
	output(7 downto 0) <= state(address*8 + 15 downto address*8 + 8);
end mem;

