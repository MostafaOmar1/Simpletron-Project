.PHONY: clean All

All:
	@echo "----------Building project:[ Simpletron - Debug ]----------"
	@cd "Simpletron" && "$(MAKE)" -f  "Simpletron.mk"
clean:
	@echo "----------Cleaning project:[ Simpletron - Debug ]----------"
	@cd "Simpletron" && "$(MAKE)" -f  "Simpletron.mk" clean
