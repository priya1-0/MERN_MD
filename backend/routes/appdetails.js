const router = require('express').Router();
let Appdetails = require('../models/datamodel');


router.route('/').get((req, res) => {
    Appdetails.find()
    .then(appdetails => res.json(appdetails))
    .catch(err => res.status(400).json('Error: ' + err));
});

router.route('/add').post((req, res) => {
  const applicationname = req.body.applicationname;
  const applicationurl = req.body.applicationurl;
  const version = Number(req.body.version);
  const date = Date.parse(req.body.date);

  const newAppdetails = new Appdetails({
    applicationname,
    applicationurl,
    version,
    date
    
  });

  newAppdetails.save()
  .then(() => res.json('Appdetails added!'))
  .catch(err => res.status(400).json('Error: ' + err));
  
});

router.route('/:id').get((req, res) => {
    Appdetails.findById(req.params.id)
    .then(appdetail => res.json(appdetail))
    .catch(err => res.status(400).json('Error: ' + err));
});

router.route('/:id').delete((req, res) => {
    Appdetails.findByIdAndDelete(req.params.id)
    .then(() => res.json('Appdetails deleted.'))
    .catch(err => res.status(400).json('Error: ' + err));
});



router.route('/update/:id').post((req, res) => {
    Appdetails.findById(req.params.id)
    .then(appdetail => {
      appdetail.applicationname = req.body.applicationname;
      appdetail.applicationurl = req.body.applicationurl;
      appdetail.version = Number(req.body.version);
      appdetail.date = Date.parse(req.body.date);

      appdetail.save()
        .then(() => res.json('Appdetails updated!'))
        .catch(err => res.status(400).json('Error: ' + err));
    })
    .catch(err => res.status(400).json('Error: ' + err));
});

module.exports = router;

