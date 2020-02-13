set ( CMAKE_SYSTEM_PROCESSOR cortex-m3 )

stm32_add_flags ( CMAKE_C_FLAGS
				  -mcpu=cortex-m3 
				  -mthumb 
#				  -Os 
				  -fmessage-length=0 
				  -fsigned-char 
				  -ffunction-sections 
				  -fdata-sections 
				  -ffreestanding 
				  -flto 
				  -fno-move-loop-invariants 
				  -Wall 
				  -Wextra  
#				  -g
				  )

stm32_add_flags ( CMAKE_CXX_FLAGS
				-mcpu=cortex-m3 
				-mthumb 
#				-Os 
				-fmessage-length=0 
				-fsigned-char 
				-ffunction-sections 
				-fdata-sections 
				-ffreestanding 
				-flto 
				-fno-move-loop-invariants 
				-Wall 
				-Wextra  
#				-g
				-fabi-version=0 
				-fno-exceptions 
				-fno-rtti 
				-fno-use-cxa-atexit 
				-fno-threadsafe-statics
			  )

stm32_add_flags ( CMAKE_ASM_FLAGS
				  "-mthumb"
				  "-mcpu=cortex-m3"
				  "-x"
				  "assembler-with-cpp"
				  )

stm32_add_flags ( CMAKE_EXE_LINKER_FLAGS
#				  "-Wl,--gc-sections"
#				  "-mthumb"
#				  "-mcpu=cortex-m3"
#				  "-mfloat-abi=soft"
				  -mcpu=cortex-m3 
				  -mthumb 
#				  -Os 
				  -fmessage-length=0 
				  -fsigned-char 
				  -ffunction-sections 
				  -fdata-sections 
				  -ffreestanding 
				  -flto 
				  -fno-move-loop-invariants 
				  -Wall 
				  -Wextra  
#				  -g 
				  -Xlinker 
				  --gc-sections 				  
				  -fabi-version=0 
				  -fno-exceptions 
				  -fno-rtti 
				  -fno-use-cxa-atexit 
				  -fno-threadsafe-statics
				  -Wl,-Map,"Boot.map"
				  "-L\"${PROJECT_SOURCE_DIR}/ldscripts\""
				  "-T ${STM32_LINKER_SCRIPT}"
				  )

add_definitions ( -DSTM32F1 )
