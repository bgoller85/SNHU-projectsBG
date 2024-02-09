var express = require('express');
var router = express.Router();

var tripsController = require('../controllers/trips');

router
    .route('/trips')
    .get(tripsController.tripsList);

router
    .route('/trips/:tripCode')
    .get(tripsController.tripsFindCode);

module.exports = router;