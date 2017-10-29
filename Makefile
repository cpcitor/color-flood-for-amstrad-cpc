# THIS_FILE_WILL_BE_OVERWRITTEN_BY_CDTC
# local.makefile is intended for your local custom makefiles rules (if any).
# local.makefile comes first to allow to customize default target.
-include local.Makefile
# cdtc_project.conf sets project parameters.
-include cdtc_project.conf
# cdtc_local_machine.conf is for stuff specific to this machine, like path to cpc-dev-tool-chain.
-include cdtc_local_machine.conf
# sdcc-project.Makefile is the main default makefile inside cpc-dev-tool-chain.
-include $(CDTC_ROOT)/sdcc-project.Makefile
fail_for_cannot_locate_cdtc:
	@echo 'Cannot locate cpc-dev-tool-chain main directory.'
	@echo 'Explanation: this project appears to rely on cpc-dev-tool-chain for compilation.'
	@echo 'You can get a copy from https://github.com/cpcitor/cpc-dev-tool-chain'
	@echo 'Then run:'
	@echo '/path/to/cpc-dev-tool-chain/cdtc-project-setup.sh /org/gourichon/localdata/SG/historique/2016/2016-09-19/color_flood_for_amstrad_cpc'
	@echo 'Then you can run "make" here and the project should build.'
	@false
