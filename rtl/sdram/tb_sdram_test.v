module tb_sdram_test;

reg master_clk_i;
wire sdram_clk_o;
reg sdram_clk_i;
wire led_disp_d0_o;
wire led_disp_d1_o;
wire led_disp_d2_o;
wire led_disp_d3_o;
wire led_disp_d4_o;
wire led_disp_d5_o;
wire led_disp_d6_o;
wire led_disp_d7_o;
wire [3:0] led_status;
reg pb_i;
wire sdramCntl_inst_sd_intf_cke;
wire sdramCntl_inst_sd_intf_we;
wire [12:0] sdramCntl_inst_sd_intf_addr;
wire sdramCntl_inst_sd_intf_dqml;
wire sdramCntl_inst_sd_intf_cas;
wire sdramCntl_inst_sd_intf_dqmh;
wire sdramCntl_inst_sd_intf_ras;
wire [1:0] sdramCntl_inst_sd_intf_bs;
wire sdramCntl_inst_sd_intf_cs;
wire [15:0] sdramCntl_inst_sd_intf_dq;

initial begin
    $from_myhdl(
        master_clk_i,
        sdram_clk_i,
        pb_i
    );
    $to_myhdl(
        sdram_clk_o,
        led_disp_d0_o,
        led_disp_d1_o,
        led_disp_d2_o,
        led_disp_d3_o,
        led_disp_d4_o,
        led_disp_d5_o,
        led_disp_d6_o,
        led_disp_d7_o,
        led_status,
        sdramCntl_inst_sd_intf_cke,
        sdramCntl_inst_sd_intf_we,
        sdramCntl_inst_sd_intf_addr,
        sdramCntl_inst_sd_intf_dqml,
        sdramCntl_inst_sd_intf_cas,
        sdramCntl_inst_sd_intf_dqmh,
        sdramCntl_inst_sd_intf_ras,
        sdramCntl_inst_sd_intf_bs,
        sdramCntl_inst_sd_intf_cs,
        sdramCntl_inst_sd_intf_dq
    );
end

sdram_test dut(
    master_clk_i,
    sdram_clk_o,
    sdram_clk_i,
    led_disp_d0_o,
    led_disp_d1_o,
    led_disp_d2_o,
    led_disp_d3_o,
    led_disp_d4_o,
    led_disp_d5_o,
    led_disp_d6_o,
    led_disp_d7_o,
    led_status,
    pb_i,
    sdramCntl_inst_sd_intf_cke,
    sdramCntl_inst_sd_intf_we,
    sdramCntl_inst_sd_intf_addr,
    sdramCntl_inst_sd_intf_dqml,
    sdramCntl_inst_sd_intf_cas,
    sdramCntl_inst_sd_intf_dqmh,
    sdramCntl_inst_sd_intf_ras,
    sdramCntl_inst_sd_intf_bs,
    sdramCntl_inst_sd_intf_cs,
    sdramCntl_inst_sd_intf_dq
);

endmodule
