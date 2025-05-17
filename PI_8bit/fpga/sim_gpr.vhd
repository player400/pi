--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   20:45:08 05/17/2025
-- Design Name:   
-- Module Name:   C:/Users/player401/Desktop/notatki/zak/pi/PI_8bit/fpga/sim_gpr.vhd
-- Project Name:  pi
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: general_purpose_register_block
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
 
ENTITY sim_gpr IS
END sim_gpr;
 
ARCHITECTURE behavior OF sim_gpr IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT general_purpose_register_block
    PORT(
         input_address : IN  integer;
         output_address : IN  integer;
         input : IN  std_logic_vector(7 downto 0);
         set : IN  std_logic;
         output : OUT  std_logic_vector(15 downto 0);
         clk : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal input_address : integer := 1;
   signal output_address : integer := 1;
   signal input : std_logic_vector(7 downto 0) := "10101010";
   signal set : std_logic := '0';
   signal clk : std_logic := '0';

 	--Outputs
   signal output : std_logic_vector(15 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: general_purpose_register_block PORT MAP (
          input_address => input_address,
          output_address => output_address,
          input => input,
          set => set,
          output => output,
          clk => clk
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
