# ShooterGameTest

## Game Features :
- A Gravity Gun with Hold object by `left mouse click`, and when released it will drop the ball. If you `right mouse click` while holding it, it will launch the ball.
- Skill base with `Space` for Dash and `1` for spawn Smoke.
- Quest system that you will need to kill 2 enemies and go to big blue box.

## In Game Setup :
- To create skill you can go to Content Browser > Miscellaneous > Data Asset > Skill Data Asset. You can modify the skill but in order to add a new one you need to modify the code as it coupled to Skill Behaviour.
- To create quest you can go to Content Browser > Miscellaneous > Data Asset > Quest Data Asset. This will populate all available quest.
- To define the actual quest objective you can create it by going to Content Browser > Miscellaneous > Data Asset > Quest Objective Data Asset.
- The Quest Data Asset is coupled with GameInstance.

## Code go through :
- To take a look around Gravity Gun implementation you can take a look in "ShooterGameTest\Source\ShooterGameTest\GravityGun.cpp or .h
- For Ability System you can go to "ShooterGameTest\Source\ShooterGameTest\Abilities\" For starter SkillActionComponent.cpp
- For Quest you can take a look into "ShooterGameTest\Source\ShooterGameTest\Quest\" For starter QuestManager.cpp

## Highlights :
- Robust and modular quest system.
- Damage system for manipulated object when touched enemy.
- Kill quest system.

# Things to Improve Later :
- Using Gameplay Ability System fully, as right now it is too complex to implement.
- Ability system that tightly coupled to the system.
- File and Folder naming, can be improved.
- Integration to Blueprint as most of the function is not supporting Blueprint.
- Unit Test to follow TDD as now all the function is at risk of edge cases.

# Time Spent :
- Gravity Gun - 8 hours
- Skill System - 15 hours
- Quest System - 10 hours