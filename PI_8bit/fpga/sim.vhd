--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   20:41:15 05/17/2025
-- Design Name:   
-- Module Name:   C:/Users/player401/Desktop/notatki/zak/pi/PI_8bit/fpga/sim.vhd
-- Project Name:  pi
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: registry_bank
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY sim IS
END sim;
 
ARCHITECTURE behavior OF sim IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT registry_bank
    PORT(
         clk : IN  std_logic;
         set : IN  std_logic;
         input : IN  std_logic_vector(7 downto 0);
         input_address : IN  std_logic;
         ir_output : OUT  std_logic_vector(15 downto 0);
         output : OUT  std_logic_vector(7 downto 0);
         output_address : IN  std_logic;
         acc : OUT  std_logic_vector(7 downto 0);
         pc : OUT  std_logic_vector(7 downto 0);
         alpha : OUT  std_logic_vector(7 downto 0);
         beta : OUT  std_logic_vector(7 downto 0);
         carry : OUT  std_logic;
         alu_set : IN  std_logic;
         alu_input : IN  std_logic_vector(8 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal set : std_logic := '0';
   signal input : std_logic_vector(7 downto 0) := (others => '0');
   signal input_address : std_logic := '0';
   signal output_address : std_logic := '0';
   signal alu_set : std_logic := '0';
   signal alu_input : std_logic_vector(8 downto 0) := (others => '0');

 	--Outputs
   signal ir_output : std_logic_vector(15 downto 0);
   signal output : std_logic_vector(7 downto 0);
   signal acc : std_logic_vector(7 downto 0);
   signal pc : std_logic_vector(7 downto 0);
   signal alpha : std_logic_vector(7 downto 0);
   signal beta : std_logic_vector(7 downto 0);
   signal carry : std_logic;

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: registry_bank PORT MAP (
          clk => clk,
          set => set,
          input => input,
          input_address => input_address,
          ir_output => ir_output,
          output => output,
          output_address => output_address,
          acc => acc,
          pc => pc,
          alpha => alpha,
          beta => beta,
          carry => carry,
          alu_set => alu_set,
          alu_input => alu_input
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;



      -- insert stimulus here 

      wait;
   end process;

END;
