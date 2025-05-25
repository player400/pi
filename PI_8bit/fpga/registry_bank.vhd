----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:46:23 05/17/2025 
-- Design Name: 
-- Module Name:    registry_bank - Behavioral 
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

entity registry_bank is
    Port ( clk : in  STD_LOGIC;
			  iterate: in STD_LOGIC;
           set : in  STD_LOGIC;
           input : in  STD_LOGIC_VECTOR (7 downto 0);
           input_address : in  integer;
           ir_output : out  STD_LOGIC_VECTOR (15 downto 0);
			  output: out STD_LOGIC_VECTOR (7 downto 0);
           output_address : in  integer;
           acc : out  STD_LOGIC_VECTOR (7 downto 0);
           pc : out  STD_LOGIC_VECTOR (7 downto 0);
           alpha : out  STD_LOGIC_VECTOR (7 downto 0);
           beta : out  STD_LOGIC_VECTOR (7 downto 0);
			  carry : out STD_LOGIC;
			  alu_set: in STD_LOGIC;
           alu_input : in  STD_LOGIC_VECTOR (8 downto 0) := "000000000"
			);
end registry_bank;

architecture Behavioral of registry_bank is

COMPONENT general_purpose_register_block is
    Port ( input_address : in  integer;
			  output_address: in integer;
           input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output  : out  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC);
END COMPONENT general_purpose_register_block;

COMPONENT registry_pc is
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0);
			  iterate : in STD_LOGIC;
           clk : in  STD_LOGIC);
END COMPONENT registry_pc;

COMPONENT registry_ab is
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0);
           clk : in  STD_LOGIC);
END COMPONENT registry_ab;

COMPONENT registry_acc is
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
			  carry: out STD_LOGIC;
           set : in  STD_LOGIC;
           input_alu : in  STD_LOGIC_VECTOR (8 downto 0);
           set_alu : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0);
           clk : in  STD_LOGIC);
END COMPONENT registry_acc;

SIGNAL pc_out: STD_LOGIC_VECTOR(7 downto 0);
SIGNAL pc_set: STD_LOGIC := '0';

SIGNAL alpha_out: STD_LOGIC_VECTOR(7 downto 0);
SIGNAL alpha_set: STD_LOGIC := '0';

SIGNAL beta_out: STD_LOGIC_VECTOR(7 downto 0);
SIGNAL beta_set: STD_LOGIC := '0';

SIGNAL acc_out: STD_LOGIC_VECTOR(7 downto 0);
SIGNAL acc_set: STD_LOGIC := '0';

SIGNAL gpr_out: STD_LOGIC_VECTOR(15 downto 0);
SIGNAL gpr_set: STD_LOGIC := '0';

SIGNAL full_output: STD_LOGIC_VECTOR(15 downto 0);

SIGNAL output_address_trimmed: integer;

SIGNAL gpr_in_adr: integer;
SIGNAL gpr_out_adr: integer;

begin

	gpr_bank: general_purpose_register_block PORT MAP(
		input_address => gpr_in_adr,
		output_address => gpr_out_adr,
		input => input,
		set => gpr_set,
		output => gpr_out,
		clk => clk
	);
	
	pc_reg: registry_pc PORT MAP(
		input => input,
		output => pc_out,
		set => pc_set,
		iterate => iterate,
		clk => clk
	);
	
	aplha_reg: registry_ab PORT MAP(
		input => input,
		output => alpha_out,
		set => alpha_set,
		clk =>clk
	
	);
	
	beta_reg: registry_ab PORT MAP(
		input => input,
		output => beta_out,
		set => beta_set,
		clk =>clk
	
	);
	
	accumulator: registry_acc PORT MAP(
		input => input,
		output => acc_out,
		set => acc_set,
		set_alu => alu_set,
		input_alu => alu_input,
		carry => carry,
		clk =>clk
	);
	
	output_address_trimmed <= output_address when (output_address MOD 2 = 0) else output_address - 1;
	
	full_output(7 downto 0) <= gpr_out(7 downto 0) when output_address_trimmed > 3 else
		alpha_out when output_address_trimmed = 0 else
		acc_out;
		
	full_output(15 downto 8) <= gpr_out(15 downto 8) when output_address_trimmed > 3 else
		pc_out when output_address_trimmed = 0 else
		beta_out;
	
	ir_output <= full_output;
	
	output <= full_output(15 downto 8) when (output_address MOD 2 = 0) else full_output(7 downto 0);
	
	pc_set <= set when input_address = 0 else '0';
	alpha_set <= set when input_address = 1 else '0';
	beta_set <= set when input_address = 2 else '0';
	acc_set <= set when input_address = 3 else '0';
	gpr_set <= set when input_address > 3 else '0';
	
	gpr_in_adr <= input_address - 4 when input_address > 3 else 0;
	gpr_out_adr <= output_address_trimmed - 4 when output_address_trimmed > 3 else 0;
	
	alpha <= alpha_out;
	beta <= beta_out;
	pc <= pc_out;
	acc <= acc_out;
	
	
end Behavioral;

