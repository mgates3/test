# Get parent directory, stripping trailing /.
dir_strip = $(patsubst %/,%,$(dir $(1)))

CUDA_DIR_1 = $(call dir_strip, /usr/local/bin/nvcc)

CUDA_DIR_2 = $(call dir_strip, $(call dir_strip, /usr/local/bin/nvcc))

CUDA_DIR_3 = $(call dir_strip, /usr/local/bin/nvcc/)

CUDA_DIR_4 = $(call dir_strip, $(call dir_strip, /usr/local/bin/nvcc/))

echo:
	@echo "CUDA_DIR_1 = '$(CUDA_DIR_1)'"
	@echo "CUDA_DIR_2 = '$(CUDA_DIR_2)'"
	@echo "CUDA_DIR_3 = '$(CUDA_DIR_3)'"
	@echo "CUDA_DIR_4 = '$(CUDA_DIR_4)'"
