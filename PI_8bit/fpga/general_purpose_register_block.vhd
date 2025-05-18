----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:26:44 05/17/2025 
-- Design Name: 
-- Module Name:    general_purpose_register_block - Behavioral 
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

entity general_purpose_register_block is
    Port ( input_address : in  integer;
			  output_address: in integer;
           input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output  : out  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC);
end general_purpose_register_block;

architecture Behavioral of general_purpose_register_block is
	SIGNAL state: STD_LOGIC_VECTOR(95 downto 0);
begin
	
	setter: process(clk) begin
		if rising_edge(clk) then
			if set = '1' then
				state(input_address*8 + 7 downto input_address*8) <= input;
			end if;
		end if;
	end process setter;

	output(15 downto 8) <= state(output_address*8 + 7 downto output_address*8);
	output(7 downto 0) <= state(output_address*8 + 15 downto output_address*8 + 8);
end Behavioral;

