(Sys.init)

@return-address0
D=A
@SP
A=M
M=D
@SP
AM=M+1

@LCL
D=M
@SP
A=M
M=D
@SP
AM=M+1

@ARG
D=M
@SP
A=M
M=D
@SP
AM=M+1

@THIS
D=M
@SP
A=M
M=D
@SP
AM=M+1

@THAT
D=M
@SP
A=M
M=D
@SP
AM=M+1

@0
D=A
@5
D=D+A
@SP
D=M-D
@ARG
M=D

@SP
D=M
@LCL
M=D

@Sys.main
0;JMP

(return-address0)

@1
D=A
@R13
M=D
@5
D=A
@R13
M=M+D
@SP
AM=M-1
D=M
@R13
A=M
M=D

(Sys.main$LOOP)

@Sys.main$LOOP
0;JMP

(Sys.main)

@123
D=A
@SP
A=M
M=D
@SP
AM=M+1

@return-address1
D=A
@SP
A=M
M=D
@SP
AM=M+1

@LCL
D=M
@SP
A=M
M=D
@SP
AM=M+1

@ARG
D=M
@SP
A=M
M=D
@SP
AM=M+1

@THIS
D=M
@SP
A=M
M=D
@SP
AM=M+1

@THAT
D=M
@SP
A=M
M=D
@SP
AM=M+1

@1
D=A
@5
D=D+A
@SP
D=M-D
@ARG
M=D

@SP
D=M
@LCL
M=D

@Sys.add12
0;JMP

(return-address1)

@0
D=A
@R13
M=D
@5
D=A
@R13
M=M+D
@SP
AM=M-1
D=M
@R13
A=M
M=D

@246
D=A
@SP
A=M
M=D
@SP
AM=M+1

@LCL
D=M
@FRAME
M=D
@5
D=D-A
A=D
D=M
@RET
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M
@1
D=D+A
@SP
M=D
@FRAME
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@FRAME
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@FRAME
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@FRAME
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@RET
A=M
0;JMP

(Sys.add12)

@0
D=A
@SP
A=M
M=D
@SP
AM=M+1

@0
D=A
@SP
A=M
M=D
@SP
AM=M+1

@0
D=A
@SP
A=M
M=D
@SP
AM=M+1

@0
D=A
@ARG
A=M
A=A+D
D=M
@SP
A=M
M=D
@SP
AM=M+1
@12
D=A
@SP
A=M
M=D
@SP
AM=M+1

@SP
AM=M-1
D=M
A=A-1
M=M+D

@LCL
D=M
@FRAME
M=D
@5
D=D-A
A=D
D=M
@RET
M=D
@SP
AM=M-1
D=M
@ARG
A=M
M=D
@ARG
D=M
@1
D=D+A
@SP
M=D
@FRAME
D=M
@1
D=D-A
A=D
D=M
@THAT
M=D
@FRAME
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@FRAME
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@FRAME
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@RET
A=M
0;JMP

