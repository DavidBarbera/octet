<h1>Introduction to Games Programming</h1>
<h1>Tools and Middleware</h1>
<br/>
<br/>
Reports:
<h2>Introduction to Game Programming</h2>
<h2>Name of the project: _MyInvaderers</h2>
<h2>In the \examples  folder</h2>
<br/>
I have been working on the invaderers example provided and my intention was developing a game based on the Sprite class. One of the main challenges was to give additional functionality to the space ship. I wanted to give the ability to move faster and in 2D, not just at the bottom of the screen. It took me a while to find the parts of the Octet that govern control over the keyboard. I found it in app_common.h. Using is_key_down() and cumbersome if-else statements to apply translation on the proper direction I managed to achieve it. I used defined constants N,S,E,W,NE,NW,SE,SW to make easier to know where I was assigning the translations to North, South, East, West, North East, North West, South East and South West directions from the current space ship position. Speed was just increased using the variable ship_speed.
My next step was to increase the shooting capacity of the space ship. I needed more keys for such a purpose since the movement of the space ship is controlled by the arrows keys. Therefore, I added more keys in the app_common.h file, starting from key_a = 65; to key_z. Shooting now can be control with the keys �e� for North (up), �s� for West (left), �f� for East (right), and �d� for South (down). Additionally, if you press two keys simultaneously, say �e �and �f�, the missile will be shot on the NorthEast direction, up-right, i.e., along the vector (1,1) from the space ship. It has been quite cumbersome to code all this as it needs a lot of if-else nested statements.
<br/>
Another functionality I wanted to add was a more dynamic movement of the invaderers (the enemy) on the screen. I wanted to use parametric curves in 2D and I started with (x,y)=(3sin5t,3sin3t). First, I needed to keep record of the time so I used a variable t that is increased in each simulation. Second, I needed to increment time t  in each simulation by a certain value which I used under the name delta. Once all this was set up and the function introduced in the invaderer movement function, I realised that it wasn�t moving correctly. It took me a while but I finally realised that the movement in the invaderers function is described by a translation each frame so therefore the correct equation to have the movement displayed correctly was its differentiated version (dx,dy)=((15cos5t)*delta,(9cos3t)*delta), where delta plays the role of the differential dt.
<br/>
Next challenge, I set up was to write a fragment shader. And here is where I got stuck most of the time, I manage to give some colour to the textures but I needed more technical practice in shading language. I would have added a second texture to play with relieve and make the sprites of the game more �3D�-like. I found it too complicated so, I was going to decide to change the whole structure of the game to have less characters and not based on Sprites but just game objects on scene using add_shapes() where it would be easier for me to write different fragment shaders for each game objet type. There are examples in Octet that are quite clear. But I honestly run out of time.
 I sincerely apologise for my underperformance, I haven�t been able to code my whole idea on the assignment but just a functional version of the invaderers meant just to be a practice to export functionality to my own game.
<br/>
<a href="https://www.youtube.com/watch?v=GTaingXDKwE&feature=youtu.be"> YouTube viewing of the game</a>
<br/>
<br/>
<h2>Tools and Middleware</h2>
<h2>Name of the project: PhysicsMess</h2>
<h2>in \example\MyMess folder</h2>
<br/>
Please, thanks to Raul Araujo and Jean Baptiste for short but priceless comments that allowed me not to go astray too far.
<br/>
This has been the project hardest to understand. Bullet physics is not precisely an open book. There has been a lot of trial and error in order to understand how Bullet works. One of the first steps to understand how to deal with this assignment was to download the PhysicsBullet library from its website and compile the demo. The sample projects are difficult to understand for my level but allowed me to get a feel for where to search. With VisualStudio I navigated around the classes of bullets which is probably better than reading their manual.
First understanding emerged after a while of reading boths Octet and Bullet libraries: the world of graphics doesn�t have physics but meshes and the world of physics can�t be seen without meshes. Therefore, attaching physics to meshes is been the first process to understand. Octet uses btRigidBodies from Bullet to bestow meshes with physical qualities. It does it by means of add_shapes() creating meshes and rigidbodies in one go; meshes are instantiated and rigidbodies kept in a stack usually called �world� (as long as Bullet is defined). Any shape will be bestowed with gravity, velocities, mass and so forth. By default any physical object (rigidbody) is free to move, but constraints can be added to limit the freedom of movement. Such constraints can be a Hinge, where a body may be fixed to pivot around an axis, a Spring, where the body will move like attached to an invisible spring, or a Slider, where the body can only move linearly within a segment. There are many variations of these basic constraints where bodies can be attached to each other not only to fix points in the space. Most of the challenge has been to understand all this.
<br/>
Next challenge was to be able to access rigid bodies once created with add_shapes() in order to apply constraints or access any information of the rigid body, the later very useful for collision callbacks. Since I wasn�t able to understand if there is a way to access a particular rigid body once several have been created, I made an stack of pointers to rigid bodies, each pointer with an Id (integer). The first rigid body created by add_shape() will have id 0, the second 1, the third 2, and so on. This data structure is mainly an struct bulletobject* {int id, bulletobject* btobject} created dynamically within add_shapes() whenever the rigidbody is created. This way I have an ordered stack of pointers to all rigidbodies of the �world� and I can access any of them at any time to create a Hinge, Spring, or Slider, or change any of the inner variables. I intended to use this feature to upload worlds of objects from a .CSV file instantaneaously, but I run out of time figuring out how to read properly a formatted file.
<br/>
My next step was intended to understand how to use keyboard and mouse to go around the world uploaded from the file. Once that done, implement a process of shooting spheres from the player point of view and use collision callbacks to execute certain processes once collision happen. One of these processes could be adding sound, or explore even further constraints trying to disable constraints if my shooting sphere collides with a certain rigid body under some form of constraint. It would have been nice as well to implement a Voronoi fracture of some of the rigid bodies.
I enjoyed this assignment very much but my frustration has come from a lack of time due to personal reasons. I haven�t been able to code all my learning and therefore my performance in this assignment is way under my usual standard. I sincerely apologise.<br/>
<br/>
<a href="https://www.youtube.com/watch?v=0bXh2jKwvng&feature=youtu.be"> YouTube viewing of the demo</a>



