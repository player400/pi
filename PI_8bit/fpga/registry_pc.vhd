----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:46:47 05/17/2025 
-- Design Name: 
-- Module Name:    registry_pc - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity registry_pc is
	 Generic (
			  initial: STD_LOGIC_VECTOR(7 downto 0)
	 );
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0);
			  iterate: in STD_LOGIC;
           clk : in  STD_LOGIC);
end registry_pc;

architecture Behavioral of registry_pc is
	SIGNAL state: STD_LOGIC_VECTOR(7 downto 0):= initial;
begin
	setter: process(clk) begin
		if rising_edge(clk) then
			if set = '1' then
				state <= input;
			else 
				if iterate = '1' then
					state <= std_logic_vector(to_unsigned(to_integer(unsigned(state)) + 2, state'length));
				end if;
			end if;
		end if;
	end process setter;
	output <= state;
end Behavioral;

