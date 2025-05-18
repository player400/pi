--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:13:32 05/18/2025
-- Design Name:   
-- Module Name:   C:/Users/player401/Desktop/notatki/zak/pi/PI_8bit/fpga/sim_alu.vhd
-- Project Name:  pi
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: alu
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
 
ENTITY sim_alu IS
END sim_alu;
 
ARCHITECTURE behavior OF sim_alu IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT alu
    PORT(
         input_a : IN  std_logic_vector(7 downto 0);
         input_b : IN  std_logic_vector(7 downto 0);
         output : OUT  std_logic_vector(8 downto 0);
         flag_1 : IN  std_logic;
         flag_2 : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal input_a : std_logic_vector(7 downto 0) := (others => '0');
   signal input_b : std_logic_vector(7 downto 0) := (others => '0');
   signal flag_1 : std_logic := '0';
   signal flag_2 : std_logic := '0';

 	--Outputs
   signal output : std_logic_vector(8 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
	SIGNAL clock: STD_LOGIC;
   constant clock_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: alu PORT MAP (
          input_a => input_a,
          input_b => input_b,
          output => output,
          flag_1 => flag_1,
          flag_2 => flag_2
        );

   -- Clock process definitions
   clock_process :process
   begin
		clock <= '0';
		wait for clock_period/2;
		clock <= '1';
		wait for clock_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clock_period*10;

			input_a <= "00000001";
			input_b <= "00000001";
      -- insert stimulus here 

      wait;
   end process;

END;
