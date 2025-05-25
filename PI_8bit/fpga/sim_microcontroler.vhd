--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:17:45 05/18/2025
-- Design Name:   
-- Module Name:   C:/Users/player401/Desktop/notatki/zak/pi/PI_8bit/fpga/sim_microcontroler.vhd
-- Project Name:  pi
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: microcontroller
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
 
ENTITY sim_microcontroler IS
END sim_microcontroler;
 
ARCHITECTURE behavior OF sim_microcontroler IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT microcontroller
    PORT(
         input : IN  std_logic_vector(7 downto 0);
         output : OUT  std_logic_vector(7 downto 0);
         input_confirm : IN  std_logic;
         clk : IN  std_logic;
         address : IN  integer
        );
    END COMPONENT;
    

   --Inputs
   signal input : std_logic_vector(7 downto 0) := (others => '0');
   signal input_confirm : std_logic := '0';
   signal clk : std_logic := '0';
   signal address : integer := 0;

 	--Outputs
   signal output : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: microcontroller PORT MAP (
          input => input,
          output => output,
          input_confirm => input_confirm,
          clk => clk,
          address => address
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

     
      -- insert stimulus here 

      wait;
   end process;

END;
