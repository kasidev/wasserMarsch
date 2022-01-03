

//import { template } from 'lodash';


const moment = require('moment')

const e = React.createElement;


class genusList extends React.Component{
    constructor(props){
        super(props)
    
        this.state={
        status : 'test'
        }
    }

    render(){
      
        return e("div", 
        {className: "container"},
        e("div",{className : "row justify-content-center"},


            e("div",{className : "col-4 align-items-center"},
                e("h2",{className: ""},"Sarah's Pumpensteuerung"),
                e("div",{className: "input-group mb-3"},
                    e("span",{className: "input-group-text"},"Nächste Bewässerung"),
                    e("input",{className:"form-control", type: "datetime-local"})
                ),
                /*
                e("div",{className: "input-group mb-3"},
                    e("span",{className: "input-group-text"},"Aktualisierungsrate"),
                    e("input",{className:"form-control", type: "number"})
                ),*/
                
                e("div",{className: "input-group mb-3"},
                    e("label",{className: "form-label", htmlFor: "refreshRange"},"Aktualisierungsrate"),
                    e("input",{className:"form-range", type: "range", id:"refreshRange",min:"30",max:"3000"}),
                    e("output",{},1000) 
                ),
                e("button",{className : "btn btn-primary"},"update")
            )
        )
        
        )
        
    }
}

const domContainer2 = document.querySelector('#reactSarahMenu')


function displayData (reactContainer) {
    if(reactContainer){

        ReactDOM.render(e(genusList), reactContainer)
        console.log("data received")
    }
    
}
displayData(domContainer2)


