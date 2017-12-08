# THIS_FILE_WILL_BE_OVERWRITTEN_BY_CDTC

# This Makefile links your project to the copy of cpc-dev-tool-chain to be used.
# It also provides assistance when none is found.
# This happens e.g. when this project is cloned to a new location.
# Please store this file along with your project files
# in your version control repository (e.g. git).

# cdtc_local_machine.conf is for stuff specific to this machine, like path to cpc-dev-tool-chain named CDTC_ROOT.
-include cdtc_local_machine.conf

# sdcc-project.Makefile is the main default makefile inside cpc-dev-tool-chain.
-include $(CDTC_ROOT)/sdcc-project.Makefile

# sdcc-project.Makefile automatically includes, if they exist, the following:
# * local.makefile is intended for your local custom makefiles rules (if any).
# * cdtc_project.conf sets project parameters.

# You may define custom rules in your local.Makefile.
# The first rule if your local.Makefile will be called as default.

########################################################################
# Below is fallback code: in case the main cpc-dev-tool-chain
# directory was not found, explain what to do.

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(dir $(mkfile_path))
fail_for_cannot_locate_cdtc:
	@echo 'Cannot locate cpc-dev-tool-chain main directory.'
	@echo 'Explanation: this project appears to rely on cpc-dev-tool-chain for compilation.'
	@echo 'You can get a copy from https://github.com/cpcitor/cpc-dev-tool-chain'
	@echo 'Then run:'
	@echo '/path/to/cpc-dev-tool-chain/cdtc-project-setup.sh $(current_dir)'
	@echo 'Then you can run "make" here and the project should build.'
	@false
