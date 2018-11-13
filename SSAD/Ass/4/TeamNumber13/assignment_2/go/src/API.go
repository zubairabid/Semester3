package main

import (
   "fmt"
   "github.com/gin-contrib/cors"                      // Why do we need this package?
   "github.com/gin-gonic/gin"
   "github.com/jinzhu/gorm"
   _ "github.com/mattn/go-sqlite3"
   _ "github.com/jinzhu/gorm/dialects/sqlite"           // If you want to use mysql or any other db, replace this line
)

var db *gorm.DB                                         // declaring the db globally
var err error

type Question struct{
	ID int `json:"id"`
	QuizId int `json:"quiz_id"`
	Statement string   `json:"statement"`
	Options   string `json:"options"`
	Answer    string    `json:"answer"`
}

type Quiz struct {
	ID        int    `json:"id"`
	Genre     string `json:"genre"`
	Quests []Question `json:"quests"`
}

type User struct {
	Name string `json:"name"`
	Username	string `json:"username" gorm:"primary_key"`
	Password string `json:"password"`
	Admin bool `json:"admin"`
	LoggedIn bool `json:"logged_in"`
}

type Msg struct{
	Message string `json:"message"`
}

type Genrescore struct{
	Username string
	Genre string
	Score int
}

type Quizscore struct{
	Username string
	QuizId int
	Score int
}

type Ansquery struct{
	Username string `json:"username"`
	Correct int	`json:"correct"`
	Genre string `json:"genre"`
	QuizId int `json:"quiz_id"`
}
type Lquery struct{
	Genre string `json:"genre"`
}

func main(){
	db,err = gorm.Open("sqlite3" , "./gorm.db")
	if err != nil {
		fmt.Println(err)
	}
	defer db.Close()
	db.AutoMigrate(&Quiz{}, &Question{}, &User{},&Genrescore{},&Quizscore{})

	r := gin.Default()
	r.POST("/newuser",CreateUser)
	r.POST("/user",GetUser)
	r.GET("/quizzes/", Getquizzes)                             // Creating routes for each functionality
	r.GET("/quizzes/:id", GetQuiz)
	r.POST("/quizzes", CreateQuiz)
	r.DELETE("/quizzes/:id", DeleteQuiz)
	r.GET("/users/",GetUsers)
	r.POST("/quizans",QuizAns)
	r.GET("/quizscore/:username",Qsc)
	r.POST("/leaderboard/",Leaderboard)
	r.DELETE("/users/:username",DeleteUser)
	r.Use((cors.Default()))
	r.Run(":8080")    
}
func Qsc(c *gin.Context){
	username := c.Params.ByName("username")
	var qscores []Quizscore

	if err := db.Table("quizscores").Where("username = ?", username).First(&qscores).Error; err != nil {
		c.AbortWithStatus(404)
		fmt.Println(err)
	 } else {
		
		c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
		c.JSON(200, qscores)
	 }

}

func DeleteUser(c *gin.Context){
	
	var user User
	var gscore Genrescore
	var qscore Quizscore
	username := c.Params.ByName("username")
	 
	   d := db.Table("users").Where("username = ?", username).Delete(&user)
	   g := db.Table("genrescores").Where("username = ?",username).Delete(&gscore)
	   q := db.Table("quizscores").Where("username = ?",username).Delete(&qscore)
	   fmt.Println(d)
	   fmt.Println(g)
	   fmt.Println(q)
	   
   	c.Header("access-control-allow-origin", "*")
   	c.JSON(200, gin.H{"user #" + username: "deleted"})


}

func Leaderboard(c *gin.Context){
	var lquery Lquery
	c.BindJSON(&lquery)
	var gscs []Genrescore

	if lquery.Genre=="all"{
		if err := db.Table("genrescores").Order("score desc").Find(&gscs).Error; err!=nil{
		c.AbortWithStatus(404)
		fmt.Println(err)
		} else {
		c.Header("access-control-allow-origin","*")
		c.JSON(200,gscs)
		}
	} else {
		if err := db.Table("genrescores").Where("genre = ?", lquery.Genre).Order("score desc").Find(&gscs).Error; err!=nil{
			c.AbortWithStatus(404)
			fmt.Println(err)
			} else {
			c.Header("access-control-allow-origin","*")
			c.JSON(200,gscs)
			}

	}

}

func QuizAns(c *gin.Context){
	if db.HasTable(&Genrescore{})!=true{
		db.CreateTable(&Genrescore{})
	}
	
	if db.HasTable(&Quizscore{})!=true{
		db.CreateTable(&Quizscore{})
	}

	var jmsg Msg
	var query Ansquery
	c.BindJSON(&query)
	var gscore Genrescore
	var gscoree Genrescore
	
	var qscore Quizscore
	var qscoree Quizscore
	
	if db.Table("genrescores").Where("username = ?",query.Username).Where("genre = ?",query.Genre).First(&gscore).RecordNotFound()==true{
		gscoree.Username=query.Username
		gscoree.Genre=query.Genre
		gscoree.Score=query.Correct
		db.Table("genrescores").Create(&gscoree)
	} else{
		d := db.Table("genrescores").Where("username = ?", query.Username).Where("genre = ?",query.Genre).Delete(&gscoree)
		fmt.Println(d)
		gscore.Score+=query.Correct
		db.Table("genrescores").Create(&gscore)
	}


	if db.Table("quizscores").Where("username = ?",query.Username).Where("quiz_id = ?",query.QuizId).First(&qscore).RecordNotFound()==true{
		qscoree.Username=query.Username
		qscoree.QuizId=query.QuizId
		qscoree.Score=query.Correct
		db.Table("quizscores").Create(&qscoree)
	} else{
		d := db.Table("quizscores").Where("username = ?", query.Username).Where("quiz_id = ?",query.QuizId).Delete(&qscoree)
		fmt.Println(d)
		qscore.Score=query.Correct
		db.Table("quizscores").Create(&qscore)
	}

	jmsg.Message = "Success"

	c.Header("access-control-allow-origin", "*")
	c.JSON(200,jmsg)



}

func GetUsers(c *gin.Context){
	var user []User
	if err := db.Table("users").Find(&user).Error; err!=nil{
		c.AbortWithStatus(404)
		fmt.Println(err)
	} else {
		c.Header("access-control-allow-origin","*")
		c.JSON(200,user)
	}
}

func GetUser(c *gin.Context) {
	var user User
	c.BindJSON(&user)

	var jmsg Msg
	var userr User
	if db.Table("users").Where("username = ?", user.Username).First(&userr).RecordNotFound()==true {
	jmsg.Message = "User Doesn't exist"
	c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
	c.JSON(404, jmsg)
	} else {
		if userr.Password==user.Password{
		jmsg.Message = "User logged in"
		userr.LoggedIn=!(userr.LoggedIn)
		db.Table("users").Save(&userr)
		c.Header("access-control-allow-origin", "*")
		c.JSON(200, jmsg)
		} else{
		jmsg.Message = "Wrong username or Password"
		c.Header("access-control-allow-origin", "*")
		c.JSON(401, jmsg)

	}
}

}

func CreateUser(c *gin.Context) {
	if db.HasTable(&User{})!=true{
		db.CreateTable(&User{})
	}
	var jmsg Msg
	var user User
	var userr User
	c.BindJSON(&user)
	if db.Table("users").Where("username = ?", user.Username).First(&userr).RecordNotFound()==true {
		user.LoggedIn=false
		user.Admin=false
		db.Table("users").Create(&user)
	jmsg.Message = "User successfully Created"
	c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
	c.JSON(201, jmsg)
	} else {
		jmsg.Message = "User already exists"
		c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
		c.JSON(404, jmsg)
	}
}

func GetQuiz(c *gin.Context) {
	id := c.Params.ByName("id")
	var quiz Quiz
	var ques []Question
	if err := db.Where("id = ?", id).First(&quiz).Error; err != nil {
		c.AbortWithStatus(404)
		fmt.Println(err)
	 } else {
		if err := db.Table("questions").Where("quiz_id = ?", quiz.ID).Find(&ques).Error; err != nil {
			c.AbortWithStatus(404)
			fmt.Println(err)
		}	else{
				quiz.Quests = ques
			}


		c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
		c.JSON(200, quiz)
	 }
}


func DeleteQuiz(c *gin.Context) {
	id := c.Params.ByName("id")
	var quiz Quiz
	var question Question 
	   d := db.Table("quizzes").Where("id = ?", id).Delete(&quiz)
	   e := db.Table("questions").Where("quiz_id = ?",id).Delete(&question)
	   fmt.Println(d)
	   fmt.Println(e)
	   
   	c.Header("access-control-allow-origin", "*")
   	c.JSON(200, gin.H{"id #" + id: "deleted"})
}

func CreateQuiz(c *gin.Context) {

	if db.HasTable(&Quiz{})!=true{
		db.CreateTable(&Quiz{})
	}

	if db.HasTable(&Question{})!=true{
		db.CreateTable(&Question{})
	}

	var quiz Quiz
	c.BindJSON(&quiz)
	db.Table("quizzes").Create(&quiz)
	c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
	c.JSON(201, quiz)
 }



 func Getquizzes(c *gin.Context) {
	var quizzes []Quiz
	var ques []Question
   if err := db.Find(&quizzes).Error; err != nil {
      c.AbortWithStatus(404)
      fmt.Println(err)
   } else {
	for i:=0 ; i< len(quizzes) ; i++ {
		if err := db.Table("questions").Where("quiz_id = ?", quizzes[i].ID).Find(&ques).Error; err != nil {
			c.AbortWithStatus(404)
			fmt.Println(err)
		}	else{
				quizzes[i].Quests = ques
			}
	}
	
	c.Header("access-control-allow-origin", "*") // Why am I doing this? Find out. Try running with this line commented
    c.JSON(200, quizzes)
   }
 }