----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:30:12 05/10/2025 
-- Design Name: 
-- Module Name:    top - Behavioral 
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

entity top is
	port(
		sw_i: in STD_LOGIC_VECTOR(7 downto 0);
		led_o: out STD_LOGIC_VECTOR(7 downto 0);
		clk_i: in STD_LOGIC;
		btnl_i: in STD_LOGIC;
		btnu_i: in STD_LOGIC;
		btnr_i: in STD_LOGIC;
		btnd_i: in STD_LOGIC;
		btnc_i: in STD_LOGIC
	);
end top;


architecture Behavioral of top is

COMPONENT microcontroller is
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           output : out  STD_LOGIC_VECTOR (7 downto 0);
			  input_confirm : in STD_LOGIC;
           clk : in  STD_LOGIC;
           address : in  integer);
END COMPONENT microcontroller;


SIGNAL temp: STD_LOGIC_VECTOR(7 downto 0);
SIGNAL adr: integer;

begin
	
	pi: microcontroller PORT MAP(
		input => sw_i,
		output => led_o,
		input_confirm => btnl_i,
		clk => clk_i,
		address => adr
	
	);


	temp(0) <= btnu_i;
	temp(1) <= btnc_i;
	temp(2) <= btnr_i;
	temp(3) <= btnd_i;
	temp(7 downto 4) <= "0000";

	adr <= to_integer(unsigned(temp));
end Behavioral;

