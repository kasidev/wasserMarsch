const express = require('express');
const router = express.Router();
const http = require("http")
const url = require("url")
const path = require("path")
const fs = require("fs")
const mimeTypes = require("mime-types")
const config = require("../config")
const moment = require('moment');

const testJson = {
  "nextIrrigation": 1651210200,
  "autoInterval": 0,
  "updateIntervall" : 60000
}


/* GET home page */
router.get('/', function(req, res, next) {

  if (testJson.nextIrrigation<moment().unix()) {
    testJson.nextIrrigation =  	1651469400
  }
  testJson.currentTime=moment().unix()
  testJson.currentTime=moment().format("dddd, MMMM Do YYYY, HH:mm:ss")

  res.send(testJson)
})


module.exports = router
