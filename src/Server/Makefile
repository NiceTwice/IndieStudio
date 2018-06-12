CXX	= 	g++

NAME	=	server

SRCS	=	User.cpp \
		Server.cpp \
		Chat.cpp \
		Profile.cpp \
		Order.cpp \
		Thread.cpp \
		Error.cpp \
		ServerModeManager.cpp \
		SaloonMode.cpp \
		GameMode.cpp \
		Entity.cpp \
		Creature.cpp \
		ControlableCreature.cpp \
		Skeleton.cpp \
		Warrior.cpp \
		Archer.cpp \
		Mage.cpp \
		Assassin.cpp \
		Priest.cpp \
		Buff.cpp \
		SpeedBoostBuff.cpp \
		SlowBoostBuff.cpp \
		Missile.cpp \
		ArrowMissile.cpp \
		SlowArrowMissile.cpp \
		ShurikenMissile.cpp \
		FireballMissile.cpp \
		MagicWandMissile.cpp \
		Skill.cpp \
		BodyAttackSkill.cpp \
		BowAttackSkill.cpp \
		SlowArrowSkill.cpp \
		SpeedBoostSkill.cpp \
		ArmureBoostSkill.cpp \
		HealSkill.cpp \
		ShurikenAttackSkill.cpp \
		FireballSkill.cpp \
		MagicWandSkill.cpp \
		ArmureBuff.cpp \
		EditFileLexer.cpp \
		EditFileParser.cpp \
		QuadTree.cpp \
		QuadNode.cpp \
		CreatureFactory.cpp \
		Wall.cpp \
		FireWindSkill.cpp \
		FireWindMissile.cpp \
		InFireBuff.cpp \
		main.cpp \

OBJS	=	$(SRCS:.cpp=.o)

CXXFLAGS	=  -std=c++11 -I./Header/

LDFLAGS	=	-lpthread -lOgreMain -lboost_system

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
