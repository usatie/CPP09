# Set the prefix for the directories
prefix := ex

# Find the highest numbered directory
highest := $(shell ls -1d $(prefix)* | sort -n | tail -n 1)

# Extract the number from the directory name
num := $(patsubst $(prefix)%,%,$(highest))

# Increment the number and pad it with a zero if necessary
next_num := $(shell printf '%02d' $(shell echo $(num) + 1 | bc))

newdir_name := $(prefix)$(next_num)

.PHONY: newdir all format run norm

all:
	# Build all the sub directories
	for dir in $(wildcard ex*); do make -C $$dir ; done

format:
	# Format all the sub directories
	for dir in $(wildcard ex*); do make -C $$dir format ; done

run:
	# Format all the sub directories
	for dir in $(wildcard ex*); do make -C $$dir run ; done

norm:
	# -I for ignoring case
	# -E for using extended regular expressions
	# -r for recursive
	grep -I -E "alloc|free|alloc|using|friend" -r ex* || echo "No errors found"

newdir:
	# Create the new directory
	mkdir -p $(newdir_name)
	mkdir -p $(newdir_name)/src
	cp main.cpp.template $(newdir_name)/src/main.cpp
	cp Makefile.template $(newdir_name)/Makefile
