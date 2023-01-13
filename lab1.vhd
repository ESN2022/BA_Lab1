library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity lab1 is
	port (
		clk : in std_logic;
		rst: in std_logic; 
		pio: out std_logic_vector(7 downto 0);
		pio_1: in std_logic;
		pio_2: in std_logic_vector(3 downto 0)
	);
end entity lab1;

architecture arch of lab1 is
	component lab1_sys is
		port (
			clk_clk                          : in  std_logic                    := 'X';             -- clk
			pio_0_external_connection_export : out std_logic_vector(7 downto 0);                    -- export
			pio_1_external_connection_export : in  std_logic                    := 'X';             -- export
			reset_reset_n                    : in  std_logic                    := 'X';             -- reset_n
			pio_2_external_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X')  -- export
		);
	end component lab1_sys;
begin
	u0 : component lab1_sys
		port map (
			clk_clk                          => clk,                          --                       clk.clk
			pio_0_external_connection_export => pio, -- pio_0_external_connection.export
			pio_1_external_connection_export => pio_1, -- pio_1_external_connection.export
			reset_reset_n                    => rst,                    --                     reset.reset_n
			pio_2_external_connection_export => pio_2 -- pio_2_external_connection.export
		);


end architecture;