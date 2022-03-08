#! /bin/bash

# This script is used to install the dependencies for the project.

# Colors codes.
RED="\033[1;31m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
BLUE="\033[1;34m"
PURPLE="\033[1;35m"
ORANGE="\033[0;31m"
DEFAULT="\033[0m"

# Variable used as a boolean to know if the script achieved its goal.
IS_ERROR=0

# Variable used to know if the script is running on a MacOS or a Linux.
OS=`uname`

# Variable used to know if the user has sudo privileges.
sudo -l &> /dev/null
IS_SUDO=$?

# This function will check if SDL2 is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function brewSDL2()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2" ]; then
		echo -e ${YELLOW}"SDL2 is not installed. Installing it now..."${DEFAULT}
		brew install sdl2
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2 installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2 has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2 is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_image is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function brewSDL2_image()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_image" ]; then
		echo -e ${YELLOW}"SDL2_image is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_image
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_image installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_image has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_image is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_ttf is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function brewSDL2_ttf()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_ttf" ]; then
		echo -e ${YELLOW}"SDL2_ttf is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_ttf
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_ttf installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_ttf has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_ttf is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_mixer is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function brewSDL2_mixer()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_mixer" ]; then
		echo -e ${YELLOW}"SDL2_mixer is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_mixer
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_mixer installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_mixer has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_mixer is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_net is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function brewSDL2_net()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_net" ]; then
		echo -e ${YELLOW}"SDL2_net is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_net
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_net installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_net has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_net is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_gfx is installed.
# If it is not installed, it will install it with brew.
# If any error occurs, it will return 1.
function brewSDL2_gfx()
{
	if [ ! -d "$HOME/.brew/Cellar/sdl2_gfx" ]; then
		echo -e ${YELLOW}"SDL2_gfx is not installed. Installing it now..."${DEFAULT}
		brew install sdl2_gfx
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_gfx installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_gfx has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_gfx is already installed."${DEFAULT}
	fi
}

# This function will check if brew is installed.
# If it is not installed, it will install it with curl.
# If any error occurs, it will return 1.
function checkBrew()
{
	if [ ! -d "$HOME/.brew" ]; then
		echo -e ${YELLOW}"Brew is not installed. Installing it now..."${DEFAULT}
		/bin/zsh -c "rm -rf $HOME/.brew && git clone --progress --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update"
		if [ $? -ne 0 ]; then
			echo -e ${RED}"Brew installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"Brew has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"Brew is already installed."${DEFAULT}
	fi
}


# This function will check if SDL2 is installed.
# If it is not installed, it will install it with apt-get.
# If any error occurs, it will return 1.
function aptSDL2()
{
	if [ ! -d "/usr/share/doc/libsdl2-2.0*" ]; then
		echo -e ${YELLOW}"SDL2 is not installed. Installing it now..."${DEFAULT}
		sudo apt-get install libsdl2-2.0 libsdl2-dev
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2 installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2 has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2 is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_image is installed.
# If it is not installed, it will install it with apt-get.
# If any error occurs, it will return 1.
function aptSDL2_image()
{
	if [ ! -d "/usr/share/doc/libsdl2_image-2*" ]; then
		echo -e ${YELLOW}"SDL2_image is not installed. Installing it now..."${DEFAULT}
		sudo apt-get install libsdl2-image-2.0-0
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_image installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_image has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_image is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_ttf is installed.
# If it is not installed, it will install it with apt-get.
# If any error occurs, it will return 1.
function aptSDL2_ttf()
{
	if [ ! -d "/usr/share/doc/libsdl2_ttf-2*" ]; then
		echo -e ${YELLOW}"SDL2_ttf is not installed. Installing it now..."${DEFAULT}
		sudo apt-get install libsdl2-ttf-2.0-0
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_ttf installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_ttf has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_ttf is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_mixer is installed.
# If it is not installed, it will install it with apt-get.
# If any error occurs, it will return 1.
function aptSDL2_mixer()
{
	if [ ! -d "/usr/share/doc/libsdl2_mixer-2*" ]; then
		echo -e ${YELLOW}"SDL2_mixer is not installed. Installing it now..."${DEFAULT}
		sudo apt-get install libsdl2-mixer-2.0-0
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_mixer installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_mixer has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_mixer is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_net is installed.
# If it is not installed, it will install it with apt-get.
# If any error occurs, it will return 1.
function aptSDL2_net()
{
	if [ ! -d "/usr/share/doc/libsdl2_net-2*" ]; then
		echo -e ${YELLOW}"SDL2_net is not installed. Installing it now..."${DEFAULT}
		sudo apt-get install libsdl2-net-2.0-0
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_net installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_net has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_net is already installed."${DEFAULT}
	fi
}

# This function will check if SDL2_gfx is installed.
# If it is not installed, it will install it with apt-get.
# If any error occurs, it will return 1.
function aptSDL2_gfx()
{
	if [ ! -d "/usr/share/doc/libsdl2_gfx-1*" ]; then
		echo -e ${YELLOW}"SDL2_gfx is not installed. Installing it now..."${DEFAULT}
		sudo apt-get install libsdl2-gfx-1.0-0
		if [ $? -ne 0 ]; then
			echo -e ${RED}"SDL2_gfx installation failed."${DEFAULT}
			IS_ERROR=1
			return;
		fi
		echo -e ${GREEN}"SDL2_gfx has been installed."${DEFAULT}
	else
		echo -e ${GREEN}"SDL2_gfx is already installed."${DEFAULT}
	fi
}



# This function will download a picture to the ressource folder.
# Only if the installation is successful.
function downloadPicture()
{
	if [ ! -d "./ressources/great.png" ]; then
		curl -s -o ./ressources/great.png https://cdn.intra.42.fr/users/small_chdespon.jpg
		if [ $? -ne 0 ]; then
			echo -e ${ORANGE}"Download of the picture failed."${DEFAULT}
			IS_ERROR=1
		fi
	fi
}

# This function asks the user if he wants to use brew or apt to install the dependencies.
function askForInstallation()
{
	echo -e ${YELLOW}"To install the dependencies you can use brew or apt."${DEFAULT}
	echo -e ${YELLOW}"Do you want to install dependencies with brew? (y/n)"${DEFAULT}
	while true; do
		read -p "" yn
		case $yn in
			[Yy]* ) brewInstall; break;;
			[Nn]* ) aptInstall; break;;
			* ) echo -e ${ORANGE}"Please answer yes or no."${DEFAULT};;
		esac
	done
}

function brewInstall()
{
	echo -e ${GREEN}"Installing dependencies with brew."${DEFAULT}
	checkBrew
	if [ $IS_ERROR -eq 0 ]; then
		brewSDL2
		if [ $IS_ERROR -eq 0 ]; then
			brewSDL2_image
			brewSDL2_ttf
			# brewSDL2_mixer SDL2_mixer seems to have some troubles.
			brewSDL2_net
			brewSDL2_gfx
		fi
	fi
}

function aptInstall()
{
	echo -e ${GREEN}"Installing dependencies with apt-get."${DEFAULT}
	echo -e ${BLUE}"Sudo password required."${DEFAULT}
	sudo -v
	aptSDL2
	if [ $IS_ERROR -eq 0 ]; then
		aptSDL2_image
		aptSDL2_ttf
		aptSDL2_mixer
		aptSDL2_net
		aptSDL2_gfx
	fi
}

function main()
{
	echo -e ${PURPLE}"Installing SDL2..."${DEFAULT}
	if [ $IS_SUDO -eq 0 ]; then
		askForInstallation
	else
		echo -e ${YELLOW}"You do not have sudo rights. Installing dependencies with 42's brew."${DEFAULT}
		brewInstall
	fi
	if [ $IS_ERROR -eq 0 ]; then
		downloadPicture
	fi
	if [ $IS_ERROR -eq 0 ]; then
		echo -e ${PURPLE}"SDL2 and its requirements have been installed."${DEFAULT}
	else
		echo -e ${RED}"An error occured during the installation."${DEFAULT}
		return 1
	fi
}

main