const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const applicationdetailsSchema = new Schema({
  applicationname: { type: String, required: true },
  applicationurl: { type: Buffer, required: true },
  version: { type: Number, required: true },
  date: { type: Date, required: true },
}, {
  timestamps: true,
});
 

const Applicationdetails = mongoose.model('Applicationdetails', applicationdetailsSchema);

module.exports = Applicationdetails;