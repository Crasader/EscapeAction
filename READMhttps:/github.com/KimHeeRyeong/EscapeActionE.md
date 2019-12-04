# EscapeAction
플레이 영상 : [https://www.youtube.com/watch?v=VC4d8rjUITo&t=5s](https://www.youtube.com/watch?v=VC4d8rjUITo&t=5s)

- [1) 데이터 설계](https://github.com/KimHeeRyeong/EscapeAction#1-데이터-설계)
- [2) 방 랜덤 생성](https://github.com/KimHeeRyeong/EscapeAction#2-방-랜덤-생성)
- [3) 탐색 및 아이템 획득](https://github.com/KimHeeRyeong/EscapeAction#3-탐색-및-아이템-획득)

## 1) 데이터 설계
[관련 코드] [json data folder](https://github.com/KimHeeRyeong/EscapeAction/tree/master/jsonData)   
  
  고정 데이터 :  name folder  
  맵 데이터 : draw folder  
  유동 데이터 : trans folder  

## 2) 방 랜덤 생성  
[관련 코드] [LevelDataSet](https://github.com/KimHeeRyeong/EscapeAction/blob/master/Proto/proj.win32/LevelDataSet.cpp) : 레벨에 따른 맵 데이터 세팅  
#### <Level 1 Room>  
![random 1](https://github.com/KimHeeRyeong/EscapeAction/blob/master/GIF/randomRoom1.gif.gif)
![random 2](https://github.com/KimHeeRyeong/EscapeAction/blob/master/GIF/randomRoom2.gif.gif)

## 3) 탐색 및 아이템 획득 
[관련 코드] [FurnitureUI](https://github.com/KimHeeRyeong/EscapeAction/blob/master/Proto/proj.win32/FurnitureUI.cpp) : 탐색 UI   
![search](https://github.com/KimHeeRyeong/EscapeAction/blob/master/GIF/search.gif)
  
#### <탐색 중 이동하는 경우>
![search_move](https://github.com/KimHeeRyeong/EscapeAction/blob/master/GIF/search_move.gif)
