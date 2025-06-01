----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:02:36 05/17/2025 
-- Design Name: 
-- Module Name:    registry_acc - Behavioral 
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

entity registry_acc is
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
			  carry: out STD_LOGIC;
           set : in  STD_LOGIC;
			  set_this_cycle: in STD_LOGIC;
           input_alu : in  STD_LOGIC_VECTOR (8 downto 0);
           set_alu : in  STD_LOGIC;
			  input_async: in STD_LOGIC_VECTOR (7 downto 0);
			  set_async: in STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0);
           clk : in  STD_LOGIC);
end registry_acc;

architecture Behavioral of registry_acc is
	SIGNAL state: STD_LOGIC_VECTOR(7 downto 0):= X"00";
	SIGNAL staging: STD_LOGIC_VECTOR(7 downto 0);
	SIGNAL carry_state: STD_LOGIC := '0';
begin

	stager: process(clk) begin
		if rising_edge(clk) then
			if set = '1' then
				staging <= input;
			end if;
		end if;
	end process stager;
	
	setter: process(clk) begin
		if falling_edge(clk) then
			if set_alu = '1' then
				state <= input_alu(7 downto 0);
				carry_state <= input_alu(8);
			else
				if set_this_cycle = '1' then
					state <= staging;
				end if;
			end if;
			if set_async = '1' then
				state <= input_async;
			end if;
		end if;

	end process setter;
	
	output <= state;
	carry <= carry_state;
end Behavioral;

