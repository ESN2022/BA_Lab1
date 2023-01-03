library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity lab1 is
	port (
		pio: out std_logic_vector(7 downto 0);--                       clk.clk
		rst: in std_logic;        -- pio_0_external_connection.export
		clk : in std_logic
	);
end entity lab1;

architecture arch of lab1 is
	component lab1_sys is
		port (
			pio_0_external_connection_export : out std_logic_vector(7 downto 0);        -- export
			reset_reset_n                    : in  std_logic          ; -- reset_n
			clk_clk                          : in  std_logic    -- clk
		);
	end component lab1_sys;

	begin
	
	u0 : component lab1_sys
		port map (
			pio_0_external_connection_export => pio, -- pio_0_external_connection.export
			reset_reset_n                    => rst,                    --                     reset.reset_n
			clk_clk                          =>clk                           --                       clk.clk
		);

end architecture;