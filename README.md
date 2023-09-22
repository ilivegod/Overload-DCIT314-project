
Ansa Tovia Okokon Nkposong – 10872693
Seka Bernard Junior – 10871724


Description: Our game engine is called Overload. Overload is an alternative game engine, inspired by industry standards. It is simple and has high quality modern c++.
Overload is divided into 12 modules (10 DLLS and 2 executables). The overload SDK is the core of the engine. It is a set of libraries that our applications (OVGame and OVEditor) are using. These libraries are modular and easy to extract from a game engine context.
Overload’s main features:
. Game editor
. scripting
. Windows game building
. Material editor
. 3D sound system
. Rigibody physics

Dependencies:
. OpenGL (Graphics API)
. GLFW (windowing and inputs)
. Bullet3 (Physics)
. irrKlang (Audio)
. imGui (GUI)

Compiling sources
Overload is using Premake5 to generate project files. To generate these project files, execute GenerateProjects.bat located at the root of the repository. Overload only targets windows x64.

How to use the application
The first window you'll see when launching Overload is the Project Hub. Basically, the Project Hub is a place where you can create new projects or open a new project. Projects that has already been opened will get displayed in a list. For the guide next steps, we will assume that you have created a new project.
When launching Overload for the first time, you should have an editor layout. Actually, only a few editor windows will be opened when you'll launch the editor. You can open additional windows by clicking the Window menu in the top bar.
Scene view: The Scene View can be considered as the main view of Overload editor. It will give you a real-time feedback of what is happening in your current scene.
Game view: The Game View, like the Scene View, reflects what is happening in your scene, but only from a fixed camera, which correspond to your game main camera. The editor will automatically focus the Game View when playing the scene.
Toolbar: A simple window providing some controls onto your scene. It allows you to play, pause, resume, step, and refresh your lua behaviours.
Hierarchy: The Hierarchy window shows the current scene hierarchy with relations between actors. You can select/delete/move/create actors in this view.
Inspector: In the Inspector, you'll be able to view and edit the currently selected actor. Adding, tweaking and removing components, changing actor settings (Name, tag, activation state...).
Console: As a way to communicate with you, the user, Overload is using logs. These logs (Information, Warnings, Errors), will be found into the console.
Asset View: The Asset View is useful to preview assets. You can drag and drop textures, models and materials to this view to preview them.
Project settings: This window contains every setting related to the current project you are working on. You can setup various things there, such as Graphics API settings, physics settings, startup scene...
Material editor: The Material Editor is a window in which you'll be able to edit your materials. From the attached shader to the parameters values, the visual appearance of your game is determined by how you configure your materials.

Creating a scene
when launching the editor, a default scene is shown. At any time, you can get back to this empty scene by clicking onto File -> New Scene. This scene is composed of 3 actors : 2 lights (Ambient and directional), and a camera.
Having a camera in a scene is essential for the game to show something onto the screen. We will start to build our scene from this base scene. You can go to the menu bar: File -> Save Scene and select a location within your project "Assets" folder. Once the scene has been saved, you should see a log in the console saying that your scene has successfully been saved. In order to add an actor to the scene, go to the menu bar and click onto: Actors -> Primitives -> Cube. You should now see a cube in your scene. You can now give a unique name to your new actor by editing "Name" in the Inspector window.

 We can give color to our cube. For that, you'll first need to create a material. In order to achieve this, right click onto your Assets folder in the Asset Browser, and click onto Create -> Material -> Standard. A text field should appear, this is where you can name your material. Enter a name for your new material and hit enter. What we just did here is that we've create a material using the Standard shader which is an engine shader. With Overload, you can create your very own shaders and create Empty materials that you'll configure for your custom shader using the Material Editor. But for now, we will stick with the Standard material preset. 

We can then apply the material to our cube. Select the cube onto which you want to apply your new material. Make the Inspector window visible and expand the Material Renderer header. In this section you should see "lambert1", which is the name of the material slot stored into the model file attached to this cube model. As you can see, it is currently using the :Material\Default.ovmat which is an engine material.

In order to apply your material to this actor, you'll have to drag and drop your new material from the asset browser to the "lambert1" field.

Scripting
The engine is using Lua as a scripting language. Lua itself is just a way for your to communicate with the engine.
Let's start by creating our script. Right click onto the Scripts folder in the Asset Browser window, click onto "New script...", enter a name and click enter. Currently, there is a restriction in the engine that prevent us from having a complex script folder tree, thus, all your scripts should directly be placed under the Scripts folder.

Building a game
Every project made with Overload is composed of an .ovproject file. This file is a simple INI file (key=value), containing all the settings of your project. Modifying and saving your settings in the Project Settings will modify your .ovproject file content.

As it is possible to setup your project by editing the .ovproject file, it is recommended to configure it via the Project Settings window. Let's toggle the "Development build" option on for now (It should be on by default).
The other setting we will change here is the "Start Scene". We will simply have to drag and drop our saved scene from the Asset Browser to the "Start Scene" field and click apply.

Let's now heads to the menu bar, and click onto "Build". We will use the "Temporary build" option as it is the quickest way to try our game.
If the build failed (Watch the console for logs), make sure:
•	You are using an Overload release OR you have compiled the right version of OvGame (Debug mode for this guide)
•	You haven't modified any other setting
•	The "Start Scene" is correctly setup
Let's now try a release build for our game. Simply uncheck the "Development build" option and click "Apply". 
