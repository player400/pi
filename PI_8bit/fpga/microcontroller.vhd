----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:22:54 05/18/2025 
-- Design Name: 
-- Module Name:    microcontroller - Behavioral 
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

entity microcontroller is
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           output : out  STD_LOGIC_VECTOR (7 downto 0);
			  input_confirm : in STD_LOGIC;
           clk : in  STD_LOGIC;
           address : in  integer);
end microcontroller;

architecture Behavioral of microcontroller is

	COMPONENT registry_bank is
		 Port ( 
				  clk : in  STD_LOGIC;
				  iterate: in STD_LOGIC;
				  set : in  STD_LOGIC;
				  input : in  STD_LOGIC_VECTOR (7 downto 0);
				  input_address : in  integer;
				  output: out STD_LOGIC_VECTOR (7 downto 0);
				  output_address : in  integer;
				  alu_set: in STD_LOGIC;
				  alu_input: in STD_LOGIC_VECTOR (8 downto 0);
				  alpha : out  STD_LOGIC_VECTOR (7 downto 0);
				  beta : out  STD_LOGIC_VECTOR (7 downto 0)
				 );
	END COMPONENT registry_bank;
	
	COMPONENT alu is
		 Port ( input_a : in  STD_LOGIC_VECTOR (7 downto 0);
				  input_b : in  STD_LOGIC_VECTOR (7 downto 0);
				  output : out  STD_LOGIC_VECTOR (8 downto 0);
				  flag_1 : in  STD_LOGIC;
				  flag_2 : in  STD_LOGIC);
	END COMPONENT alu;

	SIGNAL alu_set: STD_LOGIC;
	SIGNAL alu_bus: STD_LOGIC_VECTOR(8 downto 0);
	SIGNAL alpha: STD_LOGIC_VECTOR (7 downto 0);
	SIGNAL beta: STD_LOGIC_VECTOR (7 downto 0);
	
	SIGNAL temp: STD_LOGIC_VECTOR (7 downto 0);
	
	SIGNAL execute: STD_LOGIC := '1';
	SIGNAL iterate: STD_LOGIC := '1';
	
	SIGNAL set_register: STD_LOGIC;
	
	SIGNAL rq_set_register: STD_LOGIC;
begin

	ram: registry_bank PORT MAP (
		clk => clk,
		iterate => iterate,
		set => set_register,
		input => input,
		input_address => address,
		output => output,
		output_address => address,
		alu_set => alu_set,
		alu_input => alu_bus,
		alpha => alpha,
		beta => beta
	);

	arith_logic_unit: alu PORT MAP (
		input_a => alpha,
		input_b => beta,
		output => alu_bus,
		flag_1 => '0',
		flag_2 => '0'
	);
	
	set_register <= execute and iterate and rq_set_register;
	
	rq_set_register <= input_confirm;
	
	alu_set <= '1' when (set_register = '1' and (address = 1 or address = 2)) else '0';

end Behavioral;

