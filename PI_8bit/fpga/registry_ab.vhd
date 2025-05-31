----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:59:50 05/17/2025 
-- Design Name: 
-- Module Name:    registry_ab - Behavioral 
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

entity registry_ab is
	 Generic (
		initial : STD_LOGIC_VECTOR(7 downto 0)
	 );
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           set : in  STD_LOGIC;
           output : out  STD_LOGIC_VECTOR (7 downto 0);
           clk : in  STD_LOGIC);
end registry_ab;

architecture Behavioral of registry_ab is
	SIGNAL state: STD_LOGIC_VECTOR(7 downto 0):= initial;
begin
	setter: process(clk) begin
		if rising_edge(clk) then
			if set = '1' then
				state <= input;
			end if;
		end if;
	end process setter;
	output <= state;



end Behavioral;

