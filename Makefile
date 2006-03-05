all:
	cd 1tox ; $(MAKE)
	cd cc ; $(MAKE)
	cd ld ; $(MAKE)
	cd strip ; $(MAKE)

clean:
	cd 1tox ; $(MAKE) clean
	cd cc ; $(MAKE) clean
	cd ld ; $(MAKE) clean
	cd strip ; $(MAKE) clean
