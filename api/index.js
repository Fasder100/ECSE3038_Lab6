const express = require("express");
const mongoose = require("mongoose");


const app = express();
app.use(express.json());

mongoose.connect('mongodb+srv://User3:qazxsw123@cluster0.gu3mc.mongodb.net/TankDB?retryWrites=true&w=majority', {useNewUrlParser: true, useUnifiedTopology: true});


const Level = new mongoose.Schema({
tank_id: {
    type: Number,
    required: true

},
percentage_full: {
    type: Number,
    required: true

},


});


const suc_cess = {
	"success": true,
	"msg": "data saved in database successfully",
	"date": Date(),
}


const Data = mongoose.model('Level', Level);

// app.get("/data", (req,res)=>{
//     Data.find( (err, value) =>{
//         if (err)res.status(400).json("Bad Request");
//         res.json(value);
//     }); 

// });

app.post("/tank", (req,res) => {

        var p_full = 100 - (((req.body.water_level-10)/190)*100);
    let newData = new Data({
        tank_id: req.body.tank_id,
        percentage_full: p_full

    })

    newData.save((err, data) => {

        if(err) res.status(400).json("Bad Request");
        res.json(suc_cess);


    });



});

app.listen(5000);