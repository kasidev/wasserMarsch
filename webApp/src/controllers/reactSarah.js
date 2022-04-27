

//import { template } from 'lodash';


const moment = require('moment')
const {updateItem} = require('./curd')
const {findItem} = require('./curd')

const e = React.createElement;

const dataObject=[]

class pumpenMenu extends React.Component{
    constructor(props){
        super(props)
        this.newDate=this.newDate.bind(this)
        this.newRefresh=this.newRefresh.bind(this)
        this.updateData=this.updateData.bind(this)
    
        this.state=dataObject[0][0]
    }

    newDate(e){
        const newDateValue = e.target.value
        const userMoment = moment(newDateValue,"YYYY-MM-DDTHH:mm")
        const oldState = this.state
        oldState.nextIrrigation = userMoment.unix()
        this.setState(oldState)
        
    }
    newRefresh(e){
        const newRefreshValue = e.target.value
        const oldState = this.state
        oldState.updateIntervall = newRefreshValue
        this.setState(oldState)    
    }

    updateData(){
        const updateData = this.state
        updateItem({
            itemId :"fb8ecb99-bd48-4a4d-a152-7a93b99b102b",
            key : "nextIrrigation",
            value : updateData.nextIrrigation
        })
        updateItem({
            itemId :"fb8ecb99-bd48-4a4d-a152-7a93b99b102b",
            key : "updateIntervall",
            value : updateData.updateIntervall
        })
    

    }

    render(){
      
        return e("div", 
        {className: "container"},
        e("div",{className : "row justify-content-center"},


            e("div",{className : "col-12 align-items-center"},
                e("h2",{className: ""},"Sarah's Pumpensteuerung"),
                e("div",{className: "input-group mb-3"},
                    e("span",{className: "input-group-text"},"Nächste Bewässerung"),
                    e("input",
                        {className:"form-control",
                        type: "datetime-local",
                        defaultValue: moment.unix(this.state.nextIrrigation).format("YYYY-MM-DDTHH:mm"),
                        onBlur: this.newDate})
                ),
          
                
                e("div",{className: "input-group mb-3"},
                    e("label",{className: "form-label", htmlFor: "refreshRange"},"Aktualisierungsrate"),
                    e("input",
                        {className:"form-range",
                        type: "range", id:"refreshRange",
                        min:"300",
                        max:"86400",
                        //value: this.state.updateIntervall,
                        onMouseUp: this.newRefresh}),
                    e("span",{},`${Math.round(this.state.updateIntervall / 3600)} Stunden : \u00A0 `),
                    e("span",{},`${Math.round((this.state.updateIntervall % 3600)/60)} minuten`),  
                ),
                e("button",
                    {className : "btn btn-primary"
                    ,onClick: this.updateData},"update")
            )
        )
        
        )
        
    }
}

const domContainer2 = document.querySelector('#reactSarahMenu')

const getData = async () => {
   dataObject.push(await findItem("fb8ecb99-bd48-4a4d-a152-7a93b99b102b"))
   
   return Promise
}

function displayData (reactContainer) {
    if(reactContainer){
        getData().then(()=>{
            console.log(dataObject[0][0])
            ReactDOM.render(e(pumpenMenu), reactContainer)
            
        })
    }
    
}
displayData(domContainer2)


