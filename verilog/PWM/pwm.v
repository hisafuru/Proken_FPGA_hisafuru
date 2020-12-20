module pwm(
    input clk,
    input [3:0] duty,
    input reset,
    output reg out
);

parameter CYCLE = 0;
reg [15:0] cycle;
reg [3:0] count;

always @(posedge clk or negedge reset) begin
   if(reset)begin
     out <= 0;
     count <= 0;
     cycle <= 0;
   end
   
   else begin
     cycle <= (cycle == CYCLE) ? 0 : cycle + 1;
     count <= count + (cycle == 0);
     out <= (duty >= count);
   end
end

endmodule