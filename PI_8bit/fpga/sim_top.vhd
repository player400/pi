--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:14:11 05/31/2025
-- Design Name:   
-- Module Name:   C:/Users/player401/Desktop/notatki/zak/pi/PI_8bit/fpga/sim_top.vhd
-- Project Name:  pi
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: top
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
 
ENTITY sim_top IS
END sim_top;
 
ARCHITECTURE behavior OF sim_top IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT top
    PORT(
         sw_i : IN  std_logic_vector(7 downto 0);
         led_o : OUT  std_logic_vector(7 downto 0);
         clk_i : IN  std_logic;
         btnl_i : IN  std_logic;
         btnu_i : IN  std_logic;
         btnr_i : IN  std_logic;
         btnd_i : IN  std_logic;
         btnc_i : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal sw_i : std_logic_vector(7 downto 0) := (others => '0');
   signal clk_i : std_logic := '0';
   signal btnl_i : std_logic := '0';
   signal btnu_i : std_logic := '0';
   signal btnr_i : std_logic := '0';
   signal btnd_i : std_logic := '0';
   signal btnc_i : std_logic := '0';

 	--Outputs
   signal led_o : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_i_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: top PORT MAP (
          sw_i => sw_i,
          led_o => led_o,
          clk_i => clk_i,
          btnl_i => btnl_i,
          btnu_i => btnu_i,
          btnr_i => btnr_i,
          btnd_i => btnd_i,
          btnc_i => btnc_i
        );

   -- Clock process definitions
   clk_i_process :process
   begin
		clk_i <= '0';
		wait for clk_i_period/2;
		clk_i <= '1';
		wait for clk_i_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.

		
		while 1 = 1 loop
			wait for clk_i_period*500;
			btnr_i <= '1';
			wait for clk_i_period*5;
			btnr_i <= '0';
		end loop;
      -- insert stimulus here 

      wait;
   end process;

END;
