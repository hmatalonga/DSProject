.PHONY: clean All

All:
	@echo "----------Building project:[ ProjectoED - Debug ]----------"
	@$(MAKE) -f  "ProjectoED.mk"
clean:
	@echo "----------Cleaning project:[ ProjectoED - Debug ]----------"
	@$(MAKE) -f  "ProjectoED.mk" clean
