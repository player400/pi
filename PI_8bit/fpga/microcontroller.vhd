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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity microcontroller is
	 Generic (
			  program: STD_LOGIC_VECTOR(2047 downto 0)
	 );
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           output : out  STD_LOGIC_VECTOR (7 downto 0);
			  input_confirm : in STD_LOGIC;
			  resume : in STD_LOGIC;
           clk : in  STD_LOGIC
	 );
end microcontroller;

architecture Behavioral of microcontroller is

	COMPONENT registry_bank is
		 Generic (
			     initial: STD_LOGIC_VECTOR(127 downto 0)
		 );
		 Port ( 
				  clk : in  STD_LOGIC;
				  iterate: in STD_LOGIC;
				  set : in  STD_LOGIC;
				  acc_set_this_cycle: in STD_LOGIC;
				  input : in  STD_LOGIC_VECTOR (7 downto 0);
				  input_address : in  integer;
				  output: out STD_LOGIC_VECTOR (7 downto 0);
				  ir_output : out  STD_LOGIC_VECTOR (15 downto 0);
				  output_address : in  integer;
				  alu_set: in STD_LOGIC;
				  carry : out STD_LOGIC;
				  alu_input: in STD_LOGIC_VECTOR (8 downto 0);
				  acc_input_async: in STD_LOGIC_VECTOR (7 downto 0);
				  acc_set_async: in STD_LOGIC;
				  acc : out  STD_LOGIC_VECTOR (7 downto 0);
				  pc : out  STD_LOGIC_VECTOR (7 downto 0);
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
	
	COMPONENT memory is
	 Generic (
			  initial: STD_LOGIC_VECTOR(1919 downto 0)
	 );
    Port ( address : in  integer;
           input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
			  output: out STD_LOGIC_VECTOR (7 downto 0);
           ir_output : out  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC);
	END COMPONENT memory;
	
	COMPONENT flag_register is
    Port ( clk : in  STD_LOGIC;
           set : in  STD_LOGIC;
			  resume : in STD_LOGIC;
           flag_number : in  integer;
           value : in  STD_LOGIC;
           carry : in  STD_LOGIC;
           include_carry : in  STD_LOGIC;
           memory : in  STD_LOGIC_VECTOR(7 downto 0);
           include_memory : in  STD_LOGIC;
           negate : in  STD_LOGIC;
           operation : in  STD_LOGIC;
           hf : out  STD_LOGIC;
           sf : out  STD_LOGIC;
           af1 : out  STD_LOGIC;
           af2 : out  STD_LOGIC);
	END COMPONENT flag_register;
	
	COMPONENT ir IS
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
           clk : in  STD_LOGIC);
	END COMPONENT ir;

	SIGNAL ir_input : STD_LOGIC_VECTOR (15 downto 0);
   SIGNAL opcode : STD_LOGIC;
	
   SIGNAL mov_reverse : STD_LOGIC;
   SIGNAL mov_registry_number_vector : STD_LOGIC_VECTOR (3 downto 0);
	SIGNAL mov_registry_number : integer;
	
   SIGNAL ir_address_vector : STD_LOGIC_VECTOR (7 downto 0);
	SIGNAL ir_address: integer;
	
	SIGNAL hf: STD_LOGIC;
	SIGNAL sf: STD_LOGIC;
	SIGNAL af1: STD_LOGIC;
	SIGNAL af2: STD_LOGIC;
	
	SIGNAL flag_number_vector: STD_LOGIC_VECTOR(1 downto 0);
	SIGNAL flag_number: integer;
	SIGNAL flag_value: STD_LOGIC;
	SIGNAL flag_include_carry: STD_LOGIC;
	SIGNAL flag_include_memory: STD_LOGIC;
	SIGNAL flag_negate: STD_LOGIC;
	SIGNAL flag_operation: STD_LOGIC;
	SIGNAL carry: STD_LOGIC;

	
	SIGNAL alu_set: STD_LOGIC;
	SIGNAL alu_bus: STD_LOGIC_VECTOR(8 downto 0);
	SIGNAL alpha: STD_LOGIC_VECTOR (7 downto 0);
	SIGNAL beta: STD_LOGIC_VECTOR (7 downto 0);
	
	SIGNAL temp: STD_LOGIC_VECTOR (7 downto 0);
	
	SIGNAL execute: STD_LOGIC := '1';
	SIGNAL iterate: STD_LOGIC := '1';
	
	SIGNAL set_register: STD_LOGIC;
	SIGNAL set_memory: STD_LOGIC;
	SIGNAL set_flag: STD_LOGIC;
	
	SIGNAL rq_set_register: STD_LOGIC;
	SIGNAL rq_set_memory: STD_LOGIC;
	SIGNAL rq_set_flag: STD_LOGIC;
	
	SIGNAL register_output: STD_LOGIC_VECTOR(7 downto 0);
	SIGNAL memory_output: STD_LOGIC_VECTOR(7 downto 0);
	
	SIGNAL ir_register_output: STD_LOGIC_VECTOR(15 downto 0);
	SIGNAL ir_memory_output: STD_LOGIC_VECTOR(15 downto 0);
	
	SIGNAL registry_input_address: integer;
	SIGNAL registry_output_address: integer;
	SIGNAL memory_address: integer := 30;
	
	SIGNAL current_memreg_address: integer;
	SIGNAL register_as_memory_address: integer;
	
	SIGNAL general_bus: STD_LOGIC_VECTOR(7 downto 0);
	
	SIGNAL pc_vector: STD_LOGIC_VECTOR(7 downto 0);
	SIGNAL pc: integer;
	SIGNAL acc: STD_LOGIC_VECTOR(7 downto 0);
	
	SIGNAL acc_set_this_cycle: STD_LOGIC := '0';
	
begin

	instruction: ir PORT MAP (
		input => ir_input,
      opcode => opcode,
      mov_reverse => mov_reverse,
      mov_registry_number => mov_registry_number_vector,
      flag_flag_number => flag_number_vector,
      flag_negate => flag_negate,
      flag_carry => flag_include_carry,
      flag_memory => flag_include_memory,
      flag_operation => flag_operation,
      flag_value => flag_value,
      address => ir_address_vector,
      clk => clk
	);

	registers: registry_bank 
	GENERIC MAP (
		initial => program(127 downto 0)
	)
	PORT MAP (
		clk => clk,
		iterate => iterate,
		set => set_register,
		acc_set_this_cycle => acc_set_this_cycle,
		input => general_bus,
		input_address => registry_input_address,
		output => register_output,
		ir_output => ir_register_output,
		output_address => registry_output_address,
		alu_set => alu_set,
		carry => carry,
		alu_input => alu_bus,
		alpha => alpha,
		beta => beta,
		acc_input_async => input,
		acc_set_async => input_confirm,
		acc => acc,
		pc => pc_vector
	);

	arith_logic_unit: alu PORT MAP (
		input_a => alpha,
		input_b => beta,
		output => alu_bus,
		flag_1 => af1,
		flag_2 => af2
	);
	
	ram: memory
	GENERIC MAP (
		initial => program(2047 downto 128)
	)
	PORT MAP (
		address => memory_address,
		input => general_bus,
		set => set_memory,
		output => memory_output,
		ir_output => ir_memory_output,
		clk => clk
	);
	
	flags: flag_register PORT MAP (
		clk => clk,
      set => set_flag,
		resume => resume,
      flag_number => flag_number,
      value => flag_value,
      carry => carry,
      include_carry => flag_include_carry,
      memory => general_bus,
      include_memory => flag_include_memory,
      negate => flag_negate,
      operation => flag_operation,
      hf => hf,
      sf => sf,
      af1 => af1,
      af2 => af2
	);
	
	set_register <= execute and iterate and rq_set_register;
	set_memory <= execute and iterate and rq_set_memory;
	set_flag <= (iterate and rq_set_flag) when flag_number = 1 else (iterate and execute and rq_set_flag);
	
	alu_set <= '1' when ((execute = '1' and iterate = '1') and (opcode = '0' and (( mov_reverse = '0' and (mov_registry_number = 1 or mov_registry_number = 2)) or ( mov_reverse = '1' and (ir_address = 1 or ir_address = 2) )))) else '0';
	acc_set_this_cycle <= '1' when ((execute = '1' and iterate = '1') and (opcode = '0' and ((mov_reverse = '0' and mov_registry_number = 3) or (mov_reverse = '1' and ir_address = 3)))) else '0';
	
	rq_set_memory <= '1' when (opcode = '0' and (mov_reverse='1' and ir_address>15)) else '0';
	rq_set_register <= '0' when (opcode = '1' or (mov_reverse='1' and ir_address>15)) else '1';
	rq_set_flag <= opcode;
	
	flag_number <= to_integer(unsigned(flag_number_vector));
	ir_address <= to_integer(unsigned(ir_address_vector));
	mov_registry_number <= to_integer(unsigned(mov_registry_number_vector));
	pc <= to_integer(unsigned(pc_vector));
	
	output <= acc;
		
	iterate <= not hf;
	
	execute <= not sf;
	
	
	general_bus <= register_output when ((current_memreg_address < 16 and (opcode = '1' or mov_reverse = '0')) or (opcode = '0' and mov_reverse = '1')) else memory_output;
	

	
	memory_address <= current_memreg_address - 16 when current_memreg_address > 15 else 0;
	
	register_as_memory_address <= current_memreg_address when current_memreg_address < 16 else 0;
	
	current_memreg_address <= ir_address when clk = '0' else pc;
	registry_output_address <= register_as_memory_address when clk = '1' or (opcode='1' or mov_reverse='0') else mov_registry_number;
	registry_input_address <= register_as_memory_address when mov_reverse = '1' else mov_registry_number;
	
	ir_input <= ir_register_output when current_memreg_address < 16 else ir_memory_output;
	

end Behavioral;

