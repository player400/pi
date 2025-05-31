----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:14:37 05/18/2025 
-- Design Name: 
-- Module Name:    flag_register - Behavioral 
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

entity flag_register is
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
end flag_register;

architecture Behavioral of flag_register is
SIGNAL state: STD_LOGIC_VECTOR(3 downto 0) := "0000";

SIGNAL post_carry: STD_LOGIC;
SIGNAL post_memory: STD_LOGIC;

SIGNAL memory_or: STD_LOGIC;

SIGNAL final: STD_LOGIC;



begin
	
	setter: process(clk, resume) begin
		if rising_edge(clk) then
			if set = '1' then
				state(flag_number) <= final;
			end if;
		end if;
		if resume = '1' then
			state(0) <= '0';
		end if;
	end process setter;


	hf <= state(0);
	sf <= state(1);
	af1 <= state(2);
	af2 <= state(3);
	
	memory_or <= ((memory(0) or memory(1)) or (memory(2) or memory(3))) or ((memory(4) or memory(5)) or (memory(6) or memory(7)));
	
	post_carry <= value when include_carry = '0' else
		(value and carry) when operation = '1' else
		(value or carry);
		
	post_memory <= post_carry when include_memory = '0' else
		(post_carry and memory_or) when operation = '1' else
		(post_carry or memory_or);
		
	final <= post_memory when negate = '0' else (not post_memory);
		
end Behavioral;

