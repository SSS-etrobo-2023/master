# Copyright (c) 2009-2021 by TOPPERS Project TECS WG.

# この Makefile は、主として、テストを実行するものです。
# TECS ジェネレータの利用者は、実行する必要がありません。
# TECS ジェネレータやプラグインの開発者は、allall ターゲット
# にパスすることを確認してください。

# This Makefile mainly does TECS generator test.
# TECS generator users do not need to do this.
# If you are TECS generator and/or plugin developper,
# you should successfully pass the 'allall' target.

# do 'all' test cases which will be successfully built.
all: generator test
	@echo "Success!"
	@echo "try 'make test_err' if you want to test illegal case"
	@echo "try 'make test_exec' if you want to test EXEs"

# do 'all', do error test cases and execute all built test modules.
allall: all test_err test_exec

# build TECS generator.
#   TECS generator users do not need to do this 
#   as this software is ditributed with build done.
generator :
	cd tecsgen ; make

# do TECS generator test.
#   This is mainly for TECS generator developpers.
.PHONY : test
test :
	cd test ; make

# do TECS generator test with -r
#   This is mainly for TECS generator developpers.
test1.ram :
	cd test ; make clean ; export TECSGEN_DEFAULT_RAM=true ; make

test_err :
	cd test ; make test_err

test_exec :
	# for cmd in */*.exe */*/*.exe ; do echo $$PWD/$$cmd ; $$cmd ; done
	find test \( -name '*[Oo]paque*' -prune \) -o \( -name mruby -prune \) -o -name '*.exe' -exec echo exec: '<<<' '{}' '>>>' \; -exec '{}' \;
	cd test/mruby; make test_exec

clean :
	cd tecsgen ; make clean2
	cd test ; make clean
	rm -rf gen
	find . \( -name '*~' -o -name '*.o' -o -name '*.stackdump' \) -exec rm '{}' \;
	find test -name '*.exe' -exec rm '{}' \;



.PHONY : all_lang
all_lang: euc jp_utf8 sjis c_utf8 8859_1


.PHONY : euc
euc :
	@echo "#####################"
	@echo "#  Erase all files  #"
	@echo "#####################"
	make clean > /dev/null
	@echo ""
	@echo "########   #      #    ####### "
	@echo "#          #      #   #        "
	@echo "########   #      #   #        "
	@echo "#          #      #   #        "
	@echo "########    ######     ####### "
	@echo ""
	LANG=ja_JP.eucJP ; make all

.PHONY : jp_utf8
jp_utf8 :
	@echo "#####################"
	@echo "#  Erase all files  #"
	@echo "#####################"
	make clean > /dev/null
	@echo ""
	@echo "#      #   ########   ########              ######"
	@echo "#      #       #      #                    #      #"
	@echo "#      #       #      ######     #######    ######"
	@echo "#      #       #      #                    #      #"
	@echo " ######        #      #                     ######"
	@echo ""
	LANG=ja_JP.utf-8 ; make all

.PHONY : sjis
sjis :
	@echo "#####################"
	@echo "#  Erase all files  #"
	@echo "#####################"
	make clean > /dev/null
	@echo ""
	@echo " ######         #     ###     ###### "
	@echo "#               #      #     #       "
	@echo " ######         #      #      ###### "
	@echo "       #    #   #      #            #"
	@echo " ######      ###      ###     ###### "
	@echo ""
	LANG=ja_JP.sjis ; make all

.PHONY : c_utf8
c_utf8 :
	@echo "#####################"
	@echo "#  Erase all files  #"
	@echo "#####################"
	make clean > /dev/null
	@echo ""
	@echo " ######     #      #   ########   ########              ######"
	@echo "#           #      #       #      #                    #      #"
	@echo "#           #      #       #      ######     #######    ######"
	@echo "#           #      #       #      #                    #      #"
	@echo " ######  #   ######        #      #                     ######"
	@echo ""
	LANG=C.utf-8 ; make all

.PHONY : 8859_1
8859_1 :
	@echo "#####################"
	@echo "#  Erase all files  #"
	@echo "#####################"
	make clean > /dev/null
	@echo ""
	@echo " ######      ######     ######   ########   ######              #"
	@echo "#           #      #   #      #  #         #      #             #"
	@echo "#            ######     ######   #######    #######   #######   #"
	@echo "#           #      #   #      #         #         #             #"
	@echo " ######  #   ######     ######   #######    ######              #"
	@echo ""
	LANG=C.ISO8859-1 ; make all
