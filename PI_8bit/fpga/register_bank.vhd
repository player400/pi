----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:19:36 05/17/2025 
-- Design Name: 
-- Module Name:    ir - Behavioral 
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

entity ir is
    Port ( input : in  STD_LOGIC_VECTOR (15 downto 0);
           opcode : out  STD_LOGIC;
           mov_reverse : out  STD_LOGIC;
           mov_registry_number : out  STD_LOGIC_VECTOR (3 downto 0);
           flag_flag_number : out  STD_LOGIC_VECTOR (1 downto 0);
           flag_negate : out  STD_LOGIC;
           flag_carry : out  STD_LOGIC;
           flag_memory : out  STD_LOGIC;
           flag_operation : out  STD_LOGIC;
           flag_value : out  STD_LOGIC;
           address : out  STD_LOGIC_VECTOR (7 downto 0);
			  instruction_loaded: out STD_LOGIC;
           clk : in  STD_LOGIC);
end ir;

architecture Behavioral of ir is
	SIGNAL state: STD_LOGIC_VECTOR(15 downto 0) := "0000000000000000";
	SIGNAL state_ir: STD_LOGIC := '0';
begin

	setter: process(clk) begin
		if falling_edge(clk) then
				state <= input;
		end if;
	end process setter;
	
	opcode <= state(15);
	mov_reverse <= state(14);
	mov_registry_number <= state(13 downto 10);
	flag_flag_number <= state(14 downto 13);
	flag_value <= state(12);
	flag_carry <= state(11);
	flag_memory <= state(10);
	flag_operation <= state(9);
	flag_negate <= state(8);
	address <= state(7 downto 0);
	
	instruction_loaded <= state_ir;
	
end Behavioral;

