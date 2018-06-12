##
## Makefile for indie_studio in /home/debruy_p/projects/tek2/cpp/cpp_indie_studio
## 
## Made by Pierre Debruyne
## Login   <debruy_p@epitech.eu>
## 
## Started on  Mon Apr 25 21:51:53 2016 Pierre Debruyne
##

CXX	= 	g++

NAME	=	client

SRCS	=	BaseApplication.cpp \
		TutorialApplication.cpp \
		Readdir.cpp \
		ProfileManager.cpp\
		Profile.cpp \
		GuiMenuManager.cpp \
		MainMenu.cpp \
		JoinGameMenu.cpp \
		OptionsMenu.cpp \
		ProfileMenu.cpp \
		NewProfileMenu.cpp \
		EditProfileMenu.cpp \
		MenuView.cpp \
		LanguageMenu.cpp \
		SoundMenu.cpp \
		SaloonMenu.cpp \
		GameMenu.cpp \
		LanguageManager.cpp \
		Server.cpp \
		Order.cpp \
		ServerException.cpp \
		main.cpp \
		Entity.cpp \
		Creature.cpp \
		Warrior.cpp \
		SkeletonArcher.cpp \
		SkeletonFighter.cpp \
		SkeletonMage.cpp \
		Golem.cpp \
		Spell.cpp \
		MagicWandAttack.cpp \
		BodyAttack.cpp \
		RangedBowWindAttack.cpp \
		WindArrow.cpp \
		FireWindAttack.cpp \
		BuffFireDamage.cpp \
		SlowWindAttack.cpp \
		Shuriken.cpp \
		ShurikenAttack.cpp \
		SoundManager.cpp \
		BuffSlowBoost.cpp \
		Armure.cpp \
		ArmureBuff.cpp \
		Heal.cpp \
		SampleMissile.cpp \
		SpellFireBall.cpp \
		Buff.cpp \
		BuffSpeedBoostFire.cpp \
		SpellSpeedBoost.cpp \
		ViewManager.cpp \
		GameView.cpp \
		GameHUDManager.cpp \
		ObjectFactory.cpp \
		WorldStaticObject.cpp \
		WallCube.cpp \
		TreeCube.cpp \
		Malygos.cpp \
		Arthas.cpp \

OBJS	=	$(SRCS:.cpp=.o)

CXXFLAGS	+= -std=c++11 -I/usr/include/OGRE/Overlay -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/OGRE/Terrain -I/usr/include/cegui-0/ -I./Header/ -lpthread

LDXXFLAGS	+= -lOgreMain -lboost_system -lOIS -lOgreOverlay -lCEGUIBase-0 -lCEGUIOgreRenderer-0 -lfmodex

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) -lpthread $(OBJS) $(LDXXFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
