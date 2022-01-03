const express = require('express');
const router = express.Router();
const http = require("http")
const url = require("url")
const path = require("path")
const fs = require("fs")
const mimeTypes = require("mime-types")
const config = require("../config")

const testJson = {
  "nextIrrigation":  	1641216604,
  "autoInterval": 0,
  "updateIntervall" : 60000
}


/* GET home page */
router.get('/', function(req, res, next) {
  res.send(testJson)
})


module.exports = router
