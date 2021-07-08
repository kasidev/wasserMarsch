const CosmosClient = require('@azure/cosmos').CosmosClient
const config = require('./config')
const TaskList = require('./routes/tasklist')
const storage = require('./routes/storage')
const TaskDao = require('./models/taskDao')
const {uploadImage} = require('./routes/storage')
const {deleteImage} = require('./routes/storage')

const express = require('express')
const path = require('path')
const logger = require('morgan')
const cookieParser = require('cookie-parser')
const bodyParser = require('body-parser')
const public = require('./routes/index')



const app = express()

// view engine setup
app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'ejs')

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'))
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: false }))
app.use(cookieParser())
//app.use(express.static('public'))
app.use(express.static(path.join(__dirname, 'public')))

//Todo App:
const cosmosClient = new CosmosClient({
  endpoint: config.host,
  key: config.authKey
})
const taskDao = new TaskDao(cosmosClient, config.databaseId, config.containerId)
const taskList = new TaskList(taskDao)
taskDao
  .init(err => {
    console.error(err)
  })
  .catch(err => {
    console.error(err)
    console.error(
      'Shutting down because there was an error settinig up the database.'
    )
    process.exit(1)
  })

  app.use(public)


  


app.post('/addNew',(req, res, next) =>taskList.addNew(req, res).catch(next))
app.get('/findItem', (req, res, next) =>taskList.findItem(req, res).catch(next))
app.get('/findItemsOfType', (req, res, next) =>taskList.findItemsOfType(req, res).catch(next))
app.post('/findWithProp', (req, res, next) =>taskList.findWithProp(req, res).catch(next))
app.post('/updateItem',(req, res, next) =>taskList.itemUpdate(req, res).catch(next))
app.post('/deleteItem',(req, res, next) =>taskList.deleteItem(req, res).catch(next))
app.post('/uploadImage',(req,res,next)=>uploadImage(req, res).catch(next))
app.post('/deleteImage',(req,res,next)=>deleteImage(req, res).catch(next))


 
 //app.set('view engine', 'jade')

 // catch 404 and forward to error handler 
 app.use(function(req, res, next) {
   const err = new Error('Not Found')
   err.status = 404
   next(err)
 })

 // error handler
 app.use(function(err, req, res, next) {
   // set locals, only providing error in development
   res.locals.message = err.message
   res.locals.error = req.app.get('env') === 'development' ? err : {}

   // render the error page
   res.status(err.status || 500)
   res.send('error')
 })










 module.exports = app