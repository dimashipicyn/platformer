<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.10" tiledversion="1.11.2" name="pacman-main" tilewidth="24" tileheight="24" tilecount="60" columns="15">
 <image source="../Downloads/pacman-main.png" width="381" height="119"/>
 <tile id="0" type="ghost_red">
  <properties>
   <property name="state" value="move-right"/>
  </properties>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
  </animation>
 </tile>
 <tile id="2" type="ghost_red">
  <properties>
   <property name="state" value="move-down"/>
  </properties>
  <animation>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
  </animation>
 </tile>
 <tile id="4" type="ghost_red">
  <properties>
   <property name="state" value="move-left"/>
  </properties>
  <animation>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
  </animation>
 </tile>
 <tile id="6" type="ghost_red">
  <properties>
   <property name="state" value="move-up"/>
  </properties>
  <animation>
   <frame tileid="6" duration="100"/>
   <frame tileid="7" duration="100"/>
  </animation>
 </tile>
</tileset>
