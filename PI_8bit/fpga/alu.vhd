----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:10:01 05/18/2025 
-- Design Name: 
-- Module Name:    alu - Behavioral 
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

entity alu is
    Port ( input_a : in  STD_LOGIC_VECTOR (7 downto 0);
           input_b : in  STD_LOGIC_VECTOR (7 downto 0);
           output : out  STD_LOGIC_VECTOR (8 downto 0);
           flag_1 : in  STD_LOGIC;
           flag_2 : in  STD_LOGIC);
end alu;

architecture Behavioral of alu is
	SIGNAL sum: integer;
	SIGNAL difference: integer;
	SIGNAL nand_o: STD_LOGIC_VECTOR(7 downto 0);
	SIGNAL nor_o: STD_LOGIC_VECTOR(7 downto 0);
	
	SIGNAL arith_output: STD_LOGIC_VECTOR(8 downto 0);
	SIGNAL logic_output: STD_LOGIC_VECTOR(8 downto 0);
begin

	sum <= to_integer(unsigned(input_a)) + to_integer(unsigned(input_b));
	difference <= to_integer(unsigned(input_a)) - to_integer(unsigned(input_b));
	nand_o <= input_a NAND input_b;
	nor_o <= input_a NOR input_b;
	
	arith_output <= std_logic_vector(to_unsigned(sum, arith_output'length)) when flag_2 = '0' else std_logic_vector(to_unsigned(difference, arith_output'length));
	
	logic_output(8) <= '0';
	logic_output(7 downto 0) <= nand_o when flag_2 = '0' else nor_o;
	
	output <= logic_output when flag_1 = '1' else arith_output;
	
end Behavioral;

