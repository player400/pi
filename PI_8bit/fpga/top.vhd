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
		btnr_i: in STD_LOGIC;
		btnc_i: in STD_LOGIC
	);
end top;


architecture Behavioral of top is

COMPONENT microcontroller is
	 Generic (
			  program: STD_LOGIC_VECTOR(2047 downto 0)
	 );
    Port ( input : in  STD_LOGIC_VECTOR (7 downto 0);
           output : out  STD_LOGIC_VECTOR (7 downto 0);
			  input_confirm : in STD_LOGIC;
			  resume : in STD_LOGIC;
           clk : in  STD_LOGIC
    );
END COMPONENT microcontroller;


SIGNAL slow_clk: STD_LOGIC := '1';
SIGNAL counter: integer := 0;

SIGNAL resume_rising_edge_detector: integer := 0;

SIGNAL resume: STD_LOGIC;
SIGNAL resume_edge: STD_LOGIC;

begin
	
	pi: microcontroller 
	GENERIC MAP(
		program => x"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000F00040802040310009010000000000000000000000001000010"
	)
	PORT MAP(
		input => sw_i,
		output => led_o,
		input_confirm => btnc_i,
		resume => resume_edge,
		clk => slow_clk
	);
	
	count: process(clk_i) begin
		if rising_edge(clk_i) then
			if counter < 49 then
				counter <= counter+1;
			else
				counter <= 0;
			end if;
			
			if counter > 24 then 
				slow_clk <= '0';
			else
				slow_clk <= '1';
			end if;
		end if;
	end process count;
	
	rising_edge_detector: process(slow_clk) begin
		if  rising_edge(slow_clk) then
			if (resume = '1' or resume_rising_edge_detector > 0) then
				resume_rising_edge_detector <= resume_rising_edge_detector+1;
			end if;
			if (resume_rising_edge_detector > 2000000 and resume='0') then
				resume_rising_edge_detector <= 0;
			end if;
		end if;
	end process rising_edge_detector;

	resume <= btnr_i;

	resume_edge <= '1' when (resume_rising_edge_detector = 0 and resume = '1') else '0';

end Behavioral;

