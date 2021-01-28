
<!-- PROJECT LOGO -->
<br />
<p align="center">
  <h3 align="center">Lego Interactive</h3>

  <p align="center">
    The project allows the user to immerse in the Legos world and interact with some pieces.
    <br />
    <a href="https://github.com/rufimelo99/LegoInteractive"><strong>Check Files »</strong></a>
    <br />
    <br />
    · This project was done in Computer Graphics for Games at 
    <a href="https://tecnico.ulisboa.pt/en/">IST</a>
  </p>
</p>
Members:

* [Clémentine Abel](https://github.com/cleemabel)
* [Diogo Pinto](https://github.com/DiogoMPinto)
* [Francisco Cecílio](https://github.com/FranciscoCecilio)
* [Rui Melo](https://github.com/rufimelo99)

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#abstract">Abstract</a>
    </li>
    <li>
      <a href="#concept">Concept</a>
    </li>
    <li>
      <a href="#technical-challenges">Technical Challenges </a>
      <ul>
        <li><a href="#plastic-material">Plastic Material</a></li>
      </ul>
      <ul>
        <li><a href="#phong-illumination">Phong Illumination</a></li>
      </ul>
      <ul>
        <li><a href="#manipulating-legos">Manipulating Legos</a></li>
      </ul>
      <ul>
        <li><a href="#collision-system-">Collision System</a></li>
      </ul>
      <ul>
        <li><a href="#grouping-legos">Grouping Legos</a></li>
      </ul>
      <ul>
        <li><a href="#save-and-load">Save and Load</a></li>
      </ul>
    </li>
    <li>
      <a href="#proposed-solutions">Proposed Solutions</a>
      <ul>
        <li><a href="#plastic-material-implementation">Plastic Material</a></li>
      </ul>
      <ul>
        <li><a href="#phong-illumination-implementation">Phong Illumination</a></li>
      </ul>
      <ul>
        <li><a href="#manipulating-legos-implementation">Manipulating Legos</a></li>
      </ul>
      <ul>
        <li><a href="#collision-system-implementation">Collision System</a></li>
      </ul>
      <ul>
        <li><a href="#grouping-legos-implementation">Grouping Legos</a></li>
      </ul>
      <ul>
        <li><a href="#save-and-load-implementation">Save and Load</a></li>
      </ul>
    </li>
    <li>
      <a href="#what-went-well">What went well</a>
    </li>
    <li>
      <a href="#what-did-not-go-so-well">What did not go so well</a>
    </li>
  </ol>
</details>



<!-- abstract -->
## Abstract

This project is a scene where the user can interact with Legos. Each Lego piece can be picked up with the mouse, moved, enabling the altering of a scene. The user can also adapt the perception of the scene by changing the camera position. Each Lego is placed on a grid, that can be considered an extension of the pieces on the floor, where it should be possible to place the piece. As in the real world, Lego pieces can be connected up to each other and be moved around as a unit or, better, as a group. In this project, the texture of the pieces was also altered so there is a more immersive effect of the scene, making the pieces look more like real plastic pieces. The Lego scene should be able to be saved and loaded so the user can enjoy his progress.

<!-- concept-->
## Concept
The project aimed to enable the user to be part of a more childish experience, remoting to his younger life. Most of the 90’s kids, somewhere down their life played at least once or twice with Lego pieces. Knowing that this project enables the user to play around with Lego pieces and feel his childhood once more.

  
![](https://lh4.googleusercontent.com/RiYi4-4RP9SzCZmaOHdGbx14dlh0bs1z6wcrOpJJf0joqsnyS4H-0EHLcmZxNjbthU-I1Tspowd7rpQfFS0sruj0E09D1BedJQwaiKMWuyTGmb-pN6EzSuW5cAsAsA)![](https://lh4.googleusercontent.com/UbYROjNq8l1o0UsmgpD94cU2c78fe_hvhazJbkhOcadA2_OGWarFBWrH0Co7zOXlbRzVVgGpaWgCda7f-V3uT3D7HhlySrsmetJm0zjpKBc2VrEc43_8WQ-gGfxyVQ)  

First thing first, it was aimed for the pieces to look like real plastic pieces. Each piece would have a plastic texture making it look more real.

Secondly, it should allow the user to move freely around the pieces and create new ones for the user to create any desired scene. That same scene should be able to be saved and loaded when the user chooses.

Finally, the user would have a lego figure to move around and detect collisions with the pieces on the scene.

<!-- challenges-->
## Technical Challenges

## Plastic Material
In the real world, a lego is made out of plastic, so it was important to make the legos look like they were made out of plastic. So the challenge was to find a shader that would emulate that kind of material on the pieces.

## Phong Illumination
The main goal of implementing a phong illumination on the scene has to have a main source of lighting to the scene. The objective was to have the area where you build things illuminated so that the user could feel that his pieces were being illuminated as he’s working on them, just as if he was working on his desk.

## Manipulating Legos
The main technical challenges when implementing the manipulation of legos was the mouse picking.

-   Lego picking only works for a given horizontal plane, it can’t detect legos and pick them outside a given plane. At least this plane can be moved by the user (using “W” and “S”), but it is not the ideal solution.
    
-   In order to have the ray-tracing working, I had to implement inversion of 4x4 matrices (which is a pain) and learn how to convert screen coordinates into world coordinates (it was a technical challenge for me).
    
-   After having a lego selected we need to move it into another place in the grid. This presented another challenge: converting world coordinates into grid coordinates because the grid is not exactly over the green floor.

## Collision System

To move legos, we should take into consideration some important points: the lego bricks can be placed in a discrete world, according to the “assemblage property” of a normal lego (like in real life). Then, we have to respect collisions: a brick cannot be placed in a position already occupied.
![](https://docs.google.com/drawings/u/0/d/sOsoB9tFhRtPyGyGRkr4NDw/image?w=554&h=179&rev=29&ac=1&parent=1dni9aXliebBUhrbbVpe-krAsoy3S_Dc_)  

To handle these challenges, we use a grid configuration. This grid represents the 3D space where lego Bricks are allowed to be placed.
The grid allows to:

-   have a discrete space
    
-   memorize the placement of the legos and then have the current state of the Legos, and then to know where it is possible or not to put a brick.
-   use different kind of pieces

Then, the big goal of this part is to build a robust and truthful grid: this structure is the base of the project and will support the interaction with the user: then we have to think at all possibilities which can occur during manipulation by a user.
Another problem occurs during the development: how to turn the “rectangle” bricks. This problem is not solved, because here the grid units are not square. (then to turn it, we should take another .obj file (elegant solution), or when turning the lego we set it with another mesh (ugly solution))

## Grouping Legos

In real lego life, lego bricks can be grouped together to build cars, houses, or whatever we want. The challenge is to find a robust structure to register the group of bricks, add new legos inside, add new groups of legos inside, and remove bricks from it.

The main goal of grouping is to move several bricks at the same time. Therefore, the challenge is to respect the collisions of all the legos in a group.

  
![](https://docs.google.com/drawings/u/0/d/sAFaxjlFmBwsK_KGxjfqJ_g/image?w=536&h=160&rev=81&ac=1&parent=1dni9aXliebBUhrbbVpe-krAsoy3S_Dc_)

## Save and Load
The save and load functionality is a functionality that allows the user to load his project from a file and save its progress.

<!-- solutions-->
## Proposed Solutions

## Plastic Material Implementation
**Explored approaches**
Different kinds of implementations were tested to do the plastic material. After finding the shaders, the main problem was adjusting the material settings to make it look like plastic as much as possible and to lighten the darker shades of the material a bit. To do this, we took some time to experiment with the different attributes of the material (the ambient color, the diffuse color and the ambient color) so that we could get the feeling we wanted for the lego’s material. We ran into another problem because sometimes the shaded part of the object was too dark so we tried to duplicate the light source so that we could have a less dark shaded part, but it did not work as intended, there would appear a white spot where the shades were and we decided not to go with it.

**Final implementation**
For the final implementation, we went with a struct on the shader to represent the material characteristics and give it a plastic look. The struct contains the following elements: the ambient material vector defines what color the surface reflects under ambient lighting. This one is usually the same as the surface’s color. The diffuse material vector defines the surface under diffuse lighting. The specular material vector sets the color of the specular highlight on the surface. And finally, the shininess influences the scattering/radius of the specular highlight. By manipulating these values we obtain different colors for each brick and we highlight the type of feel we want the brick to have a plastic feel.

![](https://lh4.googleusercontent.com/1c_-g-UOAi75EkEcdgIIPkaqb5QHjzgSn2gYR-Kz15Xv-xERFgOaeOpfUenbOjsW2bkYWGqVuTJgh27hLBfwvp_NlrEANwLy0JfZ72PmGXp6E523MebWr52IENV5gw)![](https://lh4.googleusercontent.com/YdfCwfF0ifjvsNOUoBye54uNK2Rccg2QCtPg0du0jhv4Kdk1jbAkn6wYLaWmADx5b2WgINx4yDCy66NO7BruP-2a4j-s77o632FgXcfazJ9sBUpivdXNGA6s4wb_7w)![](https://lh5.googleusercontent.com/lUYKYdlZBR9BrLsNoIr4PtDrjuBJ_mCjTuw7NwBCQB7elPLdwhSseRH1eyN5j9uQL2Vfq58Wjc18mNlTzQmCywwJp4KQVt_ed_xsEq6uuHTObSUOYeQnKZBxYnoEag)


## Phong Illumination Implementation
**Explored approaches**
It was not too difficult to implement the illumination in the project. We looked for different ways to implement it, starting from the ones seen in the theoretical classes explaining the different kinds of illumination to tutorials online explaining the topic (link in the References segment). We saw that the different ways to approach the illumination produced similar effects in the way things were being illuminated so we went with the simplest way to do it, the way that is described below.

**Final implementation**
To implement the Phong lighting we added a light struct to the shader fragment file that contains the following components: it’s position, the ambient vector, the diffuse component of the light and the specular component. When it’s dark there’s always some kind of light source, ambient light represents that light.The diffuse simulates the directional impact. It is the component with the strongest influence in the light we see. The specular part of the light simulates the bright spot of a light that appears on shiny objects. Specular highlights are more related to the light color than to the material color.

  

![](https://lh3.googleusercontent.com/X3yPd2lYI1oFEVSTwVssMja2AH0WVhUD-3Rgn_78XSrHuIplFdwf3yTt7L16JG0ioL7tATdpPhynG0FWnvm-dAP0_T3Ks8LcsnqraXYf7dSS5_qbABrj52HnvALwpw)


## Manipulating Legos Implementation
**Explored approaches**
In order to do the lego manipulation we had to decide how legos could be moved by the person and how would this movement affect the scene, in particular other legos.
We decided that legos would be treated individually, meaning every piece can be moved and interacted with, and they would check for other pieces in order to detect collisions and don’t occupy the same space simultaneously. After talking to teacher Ricardo, the team decided to approach collisions between bricks by implementing a grid (discussed in 3.3). As for the manipulation, we decided that every lego could be picked by the mouse and possibly with the keyboard arrows, in case the mouse picking wasn’t enough. (We didn’t used it)

**Final implementation**
Implementing the mouse picking wasn’t straightforward to implement because it uses ray-tracing and 4x4 matrices operations. For this I had to implement 4x4 matrix inversion and write an adapted gluUnProject function, which maps window coordinates to world coordinates.

![](https://lh6.googleusercontent.com/r6JSzUnNbd1IQ04GmYdl2M0Bebx9DHwmleTkQBFs3Q_e5_4z5vNtJwjngOALoWIT5p-zQxz8Xf_84GBbKAJTF4JU2kmrsefMHQb5RhI6joA9SfSH4Qg8wIP3ThK1CQ)

To explain this function, in our camera.cpp, imagine that the camera shoots a ray into the screen and then checks for a collision with some object in the scene. To get this ray, we must convert window coordinates into world coordinates by manipulating the camera projection and view matrices. To detect collisions, we must provide a plane (or a point in that plane) to check collisions with the ray.

The initial idea was to check collisions with any lego on the scene, but our program only checks collisions with legos on a given horizontal plane (we call these the Y-Planes, for example in Fig.7 the green floor is the Y-Plane zero). The user can determine at any moment in what plane he is “working”. By pressing “W” and “S” you can make your Y-Plane go up and down.
![](https://lh3.googleusercontent.com/Q4oIpdnl3xKpMHnEkh8g3qHHIkiGVVtKRWczinXr_PT5tyg6YPS57hSdCy-EEh8ICadU0x3SYroiRCytjmiQAjzHbDhSql3Gg_RZpxRIo8pCQFpN__YRmiUxb1hJug)
After determining a collision with the plane, we store the hit point and iterate over all legos in the scene and see if they touch the hitpoint. If the hit point is inside the limits of a lego then congratulations you picked a lego with your mouse! Now you can drag it inside the same Y-plane or click “W” or “S” while holding it with the mouse to make it go up or down.

Everytime we move a lego, we translate it in the world position and inside our grid. This grid is not overlapping with the world, which implies a conversion of world coordinates into grid coordinates. So, when you drag a piece it checks in runtime if the grid positions are available.
![](https://lh3.googleusercontent.com/FVTkHagNhPs9fE5wmWSqkDkAb5RnAg9BOVub8kamrp8dHCgFHyNYokMH949leJGK5NI92FjD2j4cSdo2h2Xdj59-96crhPVSDQ7zjhKIXSbEpNy54rsD_-secXU9Dg)

## Movement and Collision Implementation
**Explored approaches**
The idea that a grid will manage our lego placement appears at the beginning of our implementation: indeed, there are not so many other possibilities to store the lego placement.

Then, the next question was, how to store information in the grid, and which information?

First, I think about a grid made of a new object class called gridUnit, in which we store if the unit is occupied, and with what. But this first idea is not entirely satisfactory, because a lego brick takes more than one unit of the grid to occupy and then we need another class. Then, the grid is finally a 3 dimensional array of booleans indicating the occupation of a unit.
As a lego needs to be placed and has a lot of different properties like its color, its position, its mesh, a lego object class is necessary.

The main challenge of this part is to move a lego correctly, taking into account the grid discretization, the other brick presented in the scene, and the groups of bricks.
Then, we need to know how to memorize and express the lego potion in 3 dimensions, and think about how to pass from the discrete world coordinate and the continuous 3D world.
The implementation of this grid had to be done in different steps: first, using only the 2*4 bricks (rectangles) with a grid of the same size (we cannot overlap two bricks), to build the main task as collision and placement management. Then, I’ve changed to a grid where the unit is sized like a 2*2 lego to include the new 2*2 mesh and try to turn the 2*4 lego.

**Final implementation**
#### Grid class
The grid class is finally quite simple, as it is just a map of the position of the existing bricks.
The different attributes of the class are:
-   nbUnitX, nbUnitY, nBUnitZ to register the size of the grid.
-   occupiedUnits which is the 3D array of booleans indicating the emplacement where lego bricks are present.
-   a vector 3D sizeUnit containing the size of the unit in the world coordinates.
Then, there are just simple methods to set a unit occupied or unoccupied, and get if a unit is occupied. The last method is just a print of the grid in the console for debugging.
  
![](https://docs.google.com/drawings/u/0/d/s1UdeEFTgybvF-15NZFYEVg/image?w=438&h=277&rev=341&ac=1&parent=1dni9aXliebBUhrbbVpe-krAsoy3S_Dc_)

#### Lego class
The lego class is constructed as follow:
*Attributes:*
-   a name to be identified
-   a color with its callback, and in the same way a highlight color to put in evidence the lego to the user when necessary. The highlight color is obtained just by adding a constant value to the red, blue and green coordinate of the lego color.
-   a pointer to the grid where the lego is placed.
-   the mesh and the grid size of the lego. The grid size permits us to know how many units of the grid take the lego and how.
-   the position is the grid gridPos expressed in the grid coordinate. As the lego takes more than one unit, gridPos is the corner with the smallest values on X and Z.

![](https://docs.google.com/drawings/u/0/d/slKcOrkkC5gO8KrGVnP7NCQ/image?w=355&h=232&rev=5&ac=1&parent=1dni9aXliebBUhrbbVpe-krAsoy3S_Dc_)

-   a pointer to the group to which the lego belongs, or a null pointer if it has no group associated (cf grouping legos in 4.8)
-   the scene node which refers to the lego in the openGL structure.
 
Then, the most important part of this class is the moove method.
Moving a lego is done in 3 different steps. Each step is done for the lego itself, and all the legos in its group.
In input of the function, we have the new grid position pos where we would like to put the lego.


**Step 1**
`Unoccupy all the units where the lego and its group are placed. It is necessary to do it here to check the collision: indeed, the moved legos cannot collide with themselves. We store the “old” occupied unit in a list, in case the movement is not possible.`

**Step 2**
`Check for all the legos if the new position is available. For the legos in the group, we have to compute the new positions from their current position in the grid. If the movement is not possible, we reoccupy all the old positions registered in the list.`

**Step 3**
`If the movement is accepted by the previous, we have to occupy the grid with the new position, and then to translate the brick node in the 3D world.`

To do all these steps, we need the method occupiedUnits: a method that returns all the grid units occupied by the lego from a certain position. To do that, we iterate on the X and Z coordinate of the attribute grid Size, add it to the gridPosition, and put this new vector in a list. Then, this list returns all the positions occupied by the current lego.

This algorithm needs to iterate 3 times over all the 8 units of the legos (4 units to square legos) in the group which is not really ideal with a large number of legos in a group. However, we cannot do it better in the way we have implemented because the grid only stores if a unit is occupied. To be more efficient, we should save in the grid which lego is which unit, and then for a movement checking, do not take into account a place occupied by a lego we are going to move.


## Save and Load Implementation
**Explored approaches**
The save and load functionality would be basically to allow the user to load his project from a file and save its progress. It would be needed to somehow store the information of each lego in a file. Knowing that, it was needed to store:
-   Its position;
-   Its shape;
-   Its color;
-   An id or other way to identify it.

**Final implementation**
The loading is static by loading the scene from a predefined text file named nono.txt. The saving would need to have the “P” key pressed to save in nono.txt as well.

To each lego, it was given a way to identify them, an id. This id allows us to access the LegoMap in our program.

Following the structure defined in the explored approaches, each line would have the information of a single lego piece. Then, it would have its id and its coordinates on the grid. It is preferred to have the coordinates of the grid instead of “real world” coordinates once after moving a lego, it would choose a position in the grid.

Also, the same line should include the path to the .obj’s being instantiated in the mesh (meshPath of each lego) and its color, which is a Vector4D.

Each .obj was edited/created using Blender, allowing us to have at our disposal multiple legos sizes and a more aesthetic floor. Since it reads the meshPath of each type of lego, it is prepared to handle other subclasses of legos, which could have other shapes and forms.

Additionally, the groups should be kept when the user loads the project again. For the first group logic, it was implemented. It was needed to see if a lego had a parent to write a new line with that information, so when the scene is loaded, groups would be formed through their ids. It was written a group of characters to indicate that further in the document, only grouping would be treated. Despite the similarities, for the second logic, saving groups was not implemented, due to some conflicts.

The final result of those files should be something like this:

*legoBlue;[10,0,2];src\legoBrickOK.obj;[0,0,1,1]
lego;[10,0,6];src\lego22.obj;[0.5,0.5,0,1]
legoGreen;[10,0,10];src\legoBrickOK.obj;[0,1,0,1]
legoRed;[10,1,2];src\lego22.obj;[0.1,0,0,1]
!!!!!!!!!!!!!!!!
legoYellow>legoGreen*


## Grouping Legos Implementation
**Explored approaches**
We have to assure that when a lego in a group is selected for a movement, all the others in its group will follow. Initially, the idea was that each Lego had one parent and if the parent piece moved, it would move the children. However, this idea is too complex, and we don’t need so much “precision”. Indeed, with a parent-children approach, to find all the grouped lego with the current one, we will need to browse all the hierarchical trees, which is a time complexity operation. Furthermore, a tree like that stores too much information, we don’t need to know which lego was grouped first and will complicate the ungrouping. A group is finally just a subset of bricks that should move together. Then, we need a structure on which it is easy to iterate to move each lego one by one.

**Final implementation**
This initial concept changed, making it instead of treating pieces as parents and children, it would be treated as groups. Each piece could, now, be part of a group and only one group at a time.

Unfortunately, due to some error in the code, sometimes when moving a piece within a certain group, it would move only some pieces, while in other times it would move all of them as intended.

The grouping and ungrouping action would be by pressing a key, calling the addInGroup(lego) function.

The grouping action is called by pressing the “G” key. If one of them has a group, it would add the remaining piece to the already existing group. In case of either not having a group, it would, first, create a group and then add both pieces.

The ungrouping action is called by pressing the “U” key. This action would remove a piece from its group (either from the group object as well as remove the reference in the lego object).
## What went well
-   Collision and movement
Using a grid to move the legos and treat their collisions was a good way to approach this problem. Our grid is scalable, as it is prepared to receive new types and shapes of Legos and still work. For this and the reasons we presented above in the document, we are very happy with the ending result of the grid.
The calculus of the occupied units work well and quickly with the mouse picking, there is no delay.
-   Mouse picking
The mouse picking we implemented works well most of the time and quickly. Sometimes it doesn’t work because you are trying to pick a lego on another floor (Y-plane) or your camera is too far away from that lego.
## What did not go so well
-   Grouping (has issues)
Grouping started as a promising way of moving multiple legos simultaneously. For the reasons explained earlier in the document, it turned out to be hard to implement and is a broken feature.

-   Turning lego (not implemented)
Rotating the retangular is one thing that should have been done in our program. However, we encountered some issues: after starting the turning function (method turn in the lego class), we realized that the grid units are not square… and then rotating a lego by 90° put it out of the grid discretization. To handle this problem, we should take a more adequate mesh.

-   Spawning bricks (not implemented)
In the start, we proposed to add/spawn legos to the scene. We explored this idea: How would the user pick which shapes to spawn? What color is the spawned brick? Where in the grid will it spawn? Among other questions, these took a special impact on our decisions because, although we could solve them by simply using a keyboard button to spawn every shape and color, we didn’t find this attractive to use: making the user remember those shortcuts. Ideally, this problem would be solved by implementing a simple Interface mechanism, in which one panel has displayed all the shapes and a second panel has the colors. The user would pick them and then click on the scene to spawn the desired lego. But this solution would take a lot of time to implement so we quit the idea of spawning new bricks and decided to add several bricks in the scene initially and let the user modify those.

-   Save and Load scenes with groups already made.
For the final implementation, the information about groups of legos is lost during the saving and the loading of the project. This occurred mainly to poor time management and some external errors (conflicts with .dll files).

