/* to do:

+ Detailansicht:
    - Zusatzinfos:
        * Prozesse: Zeitraum + Kurze Info wann das nächste Projekt ausläuft.

    - Klickbar:
        * Prozesse: Initiator?

+ Vergleich: locale compare, to_lower (für Umlaute, Groß-/Kleinschreibung)

*/

var vue = new Vue({
    el: "#app",
    data: {
        // data
        jsonData: {},
        children: [],
        locations: [],
        stakeholder: [],
        days: ["Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag"],

        // active
        listElement1: true,
        listElement2: false,
        listElement3: false,
        listElement4: false,
        listElement5: false,
        listElement6: false,
        listElement7: false,

        // sort active
        activeSort1: true,
        activeSort2: false,
        activeSort3: false,
        activeSort4: false,

        noBackButton: true,
        noSortbar: false,

        // labels
        sortLabel1: "ID",
        sortLabel2: "Name",
        sortLabel3: "Enddatum",
        sortLabel4: "Initiator",

        // hiding
        noSortItem3: false,
        noSortItem4: true,

        // filter
        filterLabel1: "Offen für Stakeholder",
        filterLabel2: "Aktiv",
        activeFilter1: false,
        activeFilter2: false,
        noFilter1: false,
        noFilter2: false,
        outtakenFilter1: [],
        outtakenFilter2: [],

        // info message if special content is selected
        selectedContentView: false,
        selectedContentViewMessage: "",

        // show
        showType: "processes",
        sortBy: "id",
        listToShow: [],
        contentList: [],
        participantsData: [],
        activeProjectsData: [],
        contentView: true,
        detailView: false,
        graphView: false,

        // detail view
        detailCardHeader: "",
        detailTableClickable: false,
        detailTableClickRow: "",
        detailAttachment: "",
        detailCardHeaderError: "Fehler",
        detailCardBodyError: "Bitte laden Sie die Seite neu und versuchen Sie es erneut.",

        // graphs
        graphProcessNames: [],
        graphProcessData: [],
        graphStakeholderNames: [],
        graphStakeholderData: [],
        showGraphs: false,

        // test
        // possible card colors:
        // #6D8BA8
        // #778899
        // #87aed3
        // #868e96 (bg-secondary from bootstrap)
        // #5b6066 (bg-secondary a bit darker)
        cardColor: "#5b6066",
        cardHeaderTextColor: "white",

        sortbarListProcesses: ["ID", "Name"],
        sortbarListLocations: ["ID", "Stadt"],
        sortbarListStakeholder: ["ID", "Name"],

        // attachments (images/pdfs)
        attachments: {
            //"https://process.stadt.de/process/0": "28 Vermessung.pdf",
            //"https://process.stadt.de/process/0": "5 Plazeichnung dummy.jpg",
            "https://process.stadt.de/process/11": "1 Grundsatzbeschluss.pdf",
            "https://process.stadt.de/process/15": "22 Baubeginn Erschliessungsstraße dummy.jpg",
            "https://process.stadt.de/process/16": "11 erschliessungsplanung dummy.jpg",
            "https://process.stadt.de/process/111": "10 Verkauf.pdf",
            "https://process.stadt.de/process/112": "2 Wettbewerbsauslobung.pdf",
            //"https://process.stadt.de/process/112": "7 Pressemitteilung wettbewerb.pdf",
            "https://process.stadt.de/process/113": "3 Rückfragenkolloquium.pdf",
            "https://process.stadt.de/process/114": "4 Wettbewerbsbearbeitung.pdf",
            "https://process.stadt.de/process/115": "5 Jurysitzung.pdf",
            "https://process.stadt.de/process/117": "6 Aufstellungsbeschluss.pdf",
            //"https://process.stadt.de/process/117": "8 Aufstellungsbeschluss.pdf",
            "https://process.stadt.de/process/118": "12 Städtbaulicher Vertrag.pdf",
            "https://process.stadt.de/process/120": "9  Veröffentlichung im Stadtanzeiger.pdf",
            "https://process.stadt.de/process/122": "13 Vorentwurf Bebauungsplan dummy.jpeg",
            "https://process.stadt.de/process/127": "16 Beschluss Auslage.pdf",
            "https://process.stadt.de/process/128": "17 Beschluss Auslage.pdf",
            "https://process.stadt.de/process/129": "18  Veröffentlichung im Stadtanzeiger.pdf",
            "https://process.stadt.de/process/132": "14 Stellungnahme.pdf",
            //"https://process.stadt.de/process/132": "20 Stellungnahme Bürger.pdf",
            //"https://process.stadt.de/process/132": "21 Abwägungsprotokoll dummy.pdf",
            //"https://process.stadt.de/process/132": "24 Stellungnahme.pdf",
            //"https://process.stadt.de/process/132": "26 Stellungnahme Bürger.pdf",
            //"https://process.stadt.de/process/132": "27 Abwägungsprotokoll dummy Kopie.pdf",
            //"https://process.stadt.de/process/133": "23 Entwurf überarbeitet dummy Kopie.jpg",
            "https://process.stadt.de/process/133": "15 Entwurf dummy.jpg",
            "https://process.stadt.de/process/138": "25 Veröffentlichung im Stadtanzeiger.pdf",
            "https://process.stadt.de/process/140": "19 Stellungnahme .pdf",
            "https://process.stadt.de/process/141": "29 Satzungsbeschluss.pdf",
            "https://process.stadt.de/process/142": "30 Satzungsbeschluss.pdf",
            "https://process.stadt.de/process/143": "31 Veröffentlichung im Stadtanzeiger.pdf",
            "https://process.stadt.de/process/144": "32 Baubeginn dummy.jpg"
        },
    },

    // stuff that takes more logic power
    /*
    computed: {
        sortArray: function () {
            function compare(a, b) {
                if (a.name < b.name)
                    return -1;
                if (a.name > b.name)
                    return 1;
                return 0;
            }

            return this.listToShow.sort(compare);
        },
    },
    */

    // methods
    methods: {

        setDefaultListToShow: function () {
            if (this.showType == "stakeholder") {
                this.listToShow = this.stakeholder;
            } else if (this.showType == "locations") {
                this.listToShow = this.locations;
            } else if (this.showType == "system") {
                this.listToShow = [this.jsonData.system];
            } else if (this.showType == "entrypoint") {
                this.listToShow = [this.jsonData.entrypoint];
            } else if (this.showType == "mainprocess") {
                this.listToShow = [this.jsonData.mainprocess];
            } else if (this.showType == "statistics") {
                this.drawGraphs();
            } else {
                // processes
                this.listToShow = this.children;
            }
        },

        setStakeholderSettings: function () {
            this.resetBars();

            this.listElement3 = true;
            this.showType = "stakeholder";
            this.sortLabel2 = "Name";
            this.sortLabel3 = "Status";
            this.noSortItem3 = false;
            this.noFilter1 = false;
            this.activeFilter1 = false;
            this.filterLabel1 = "Offene Gruppen";
            this.contentView = true;
            this.detailView = false;
        },

        setProcessSettings: function () {
            this.resetBars();

            this.listElement1 = true;
            this.showType = "processes";
            this.sortLabel2 = "Name";
            this.sortLabel3 = "Enddatum";
            this.noSortItem3 = false;
            this.noFilter1 = false;
            this.noFilter2 = false;
            this.activeFilter1 = false;
            this.activeFilter2 = false;
            this.filterLabel1 = "Offen für Stakeholder";
        },

        fillContentProcesses: function (i, newListItem) {
            var tmpLocation;
            var tmpStakeholder;

            var tmpLocation = "";
            var tmpInitiator = "";

            var shortName = "";

            // convert id to readableId
            var tmpList = this.listToShow[i].id.split("/");
            var readableID = this.capitalFirstLetter(tmpList[tmpList.length - 2]) + "/" + Number(tmpList[tmpList.length - 1]);

            // get city out of location object
            for (var k = 0; k < this.locations.length; k++) {
                if (this.locations[k].id == this.listToShow[i].location) {
                    tmpLocation = this.locations[k].city;
                    break;
                }
            }

            // get city out of location object
            for (var k = 0; k < this.stakeholder.length; k++) {
                if (this.stakeholder[k].id == this.listToShow[i].initiator) {
                    tmpInitiator = this.stakeholder[k].name;
                    break;
                }
            }

            var tmpContentList = ["ID", readableID,
                "Ort", tmpLocation,
                "Initiator", tmpInitiator
            ];

            // if name is too long it is shortened
            if (this.listToShow[i].name.length > 35) {
                shortName = this.listToShow[i].name.substr(0, 32) + "...";
            } else {
                shortName = this.listToShow[i].name;
            }

            newListItem = `
            <div id="` + this.listToShow[i].id + `" class="card mb-3 text-black" style="width: 20rem; border-color: ` + this.cardColor + `;">
                <div id="` + this.listToShow[i].id + `" class="card-header text-` + this.cardHeaderTextColor + `" style="background-color: ` + this.cardColor + `;">` + shortName + `</div>
                <div id="` + this.listToShow[i].id + `" class="card-body">
                    <table id="` + this.listToShow[i].id + `" class="table">`;

            // set content in for loop cause it would look to complicated in the code with setting the id all the time
            for (var index = 0; index < tmpContentList.length; index += 2) {
                newListItem += `
                        <tr id="` + this.listToShow[i].id + `" >
                            <th id="` + this.listToShow[i].id + `">` + tmpContentList[index] + `</th>
                            <td id="` + this.listToShow[i].id + `">` + tmpContentList[index + 1] + `</td>
                        </tr>`;
            }
            newListItem += `
                    </table>
                </div>
            <div>`;

            return newListItem;
        },

        fillContentLocations: function (i, newListItem) {
            // convert id to readableId
            var tmpList = this.listToShow[i].id.split("/");
            var readableID = this.capitalFirstLetter(tmpList[tmpList.length - 2]) + "/" + Number(tmpList[tmpList.length - 1]);
            var shortCity = "";

            // if name is too long it is shortened
            if (this.listToShow[i].city.length > 35) {
                shortCity = this.listToShow[i].city.substr(0, 32) + "...";
            } else {
                shortCity = this.listToShow[i].city;
            }

            newListItem = `
            <div id="` + this.listToShow[i].id + `" class="card mb-3 text-black" style="width: 20rem; border-color: ` + this.cardColor + `;">
                <div id="` + this.listToShow[i].id + `" class="card-header text-` + this.cardHeaderTextColor + `" style="background-color: ` + this.cardColor + `;">` + shortCity + `</div>
                <div id="` + this.listToShow[i].id + `" class="card-body">
                    <table id="` + this.listToShow[i].id + `" class="table">
                        <tr id="` + this.listToShow[i].id + `" >
                            <th id="` + this.listToShow[i].id + `">ID</th>
                            <td id="` + this.listToShow[i].id + `">` + readableID + `</td>
                        </tr>`;
            if (this.listToShow[i].address) {
                newListItem += `<tr id="` + this.listToShow[i].id + `" >
                            <th id="` + this.listToShow[i].id + `">Adresse</th>
                            <td id="` + this.listToShow[i].id + `">` + this.listToShow[i].address + `</td>
                        </tr>`;
            }
            newListItem += `
                    </table>
                </div>
            <div>`;
            return newListItem;
        },

        fillContentStakeholder: function (i, newListItem) {
            var color = "";
            var shortName = "";

            // convert id to readableId
            var tmpList = this.listToShow[i].id.split("/");
            var readableID = this.capitalFirstLetter(tmpList[tmpList.length - 2]) + "/" + Number(tmpList[tmpList.length - 1]);

            if (this.listToShow[i].type == "group closed")
                color = `text-danger`
            else
                color = `text-success`;

            // if name is too long it is shortened
            if (this.listToShow[i].name.length > 35) {
                shortName = this.listToShow[i].name.substr(0, 32) + "...";
            } else {
                shortName = this.listToShow[i].name;
            }

            var projectCounter = 0;
            for (item in this.children) {
                for (subitem in this.children[item].participants) {
                    // is the stakeholder included ?
                    if (this.children[item].participants[subitem] == this.listToShow[i].id) {
                        projectCounter++;
                        break;
                    }
                }
            }

            newListItem = `
            <div id="` + this.listToShow[i].id + `" class="card mb-3 text-black" style="width: 20rem; border-color: ` + this.cardColor + `;">
                <div id="` + this.listToShow[i].id + `" class="card-header text-` + this.cardHeaderTextColor + `" style="background-color: ` + this.cardColor + `;">` + shortName + `</div>
                <div id="` + this.listToShow[i].id + `" class="card-body">
                    <table id="` + this.listToShow[i].id + `" class="table">
                        <tr id="` + this.listToShow[i].id + `" >
                            <th id="` + this.listToShow[i].id + `">ID</th>
                            <td id="` + this.listToShow[i].id + `">` + readableID + `</td>
                        </tr>
                        <tr id="` + this.listToShow[i].id + `" >
                            <th id="` + this.listToShow[i].id + `">Status</th>
                            <td id="` + this.listToShow[i].id + `" class="` + color + `">` + this.localize(this.listToShow[i].type) + `</td>
                        </tr>
                        <tr id="` + this.listToShow[i].id + `" >
                            <th id="` + this.listToShow[i].id + `">Projekte</th>
                            <td id="` + this.listToShow[i].id + `">` + projectCounter + `</td>
                        </tr>
                    </table>
                </div>
            <div>`;
            return newListItem;
        },

        fillContent: function () {
            this.noBackButton = true;
            if (this.showGraphs) {
                this.selectedContentView = false;
                // back from detail view to graphs
                this.clickHandlerSidebar({
                    target: {
                        id: "sidebarStatistics"
                    }
                });
            } else {
                // normal content (back from detail view to normal content)
                this.noSortbar = false;
                this.contentList = [];
                this.contentView = true;
                this.detailView = false;
                var newListItem = "";

                // sort listToShow
                this.listToShow = this.sortArray();

                for (var i = 0; i < this.listToShow.length; i++) {

                    if (this.showType == "locations") {
                        newListItem = this.fillContentLocations(i, newListItem);
                    } else if (this.showType == "stakeholder") {
                        newListItem = this.fillContentStakeholder(i, newListItem);
                    } else {
                        newListItem = this.fillContentProcesses(i, newListItem);
                    }

                    // add it to list
                    this.contentList.push(newListItem);
                }
            }
        },

        sortArray: function () {
            function compareID(a, b) {
                // get id number from id string
                var tmpListA = a.id.split("/");
                var aId = Number(tmpListA[tmpListA.length - 1]);
                var tmpListB = b.id.split("/");
                var bId = Number(tmpListB[tmpListB.length - 1]);

                if (aId < bId)
                    return -1;
                if (aId > bId)
                    return 1;
                return 0;
            }

            function compareName(a, b) {
                if (a.name < b.name)
                    return -1;
                if (a.name > b.name)
                    return 1;
                return 0;
            }

            function compareCity(a, b) {
                if (a.city < b.city)
                    return -1;
                if (a.city > b.city)
                    return 1;
                return 0;
            }

            function compareLocation(a, b) {
                if (a.location < b.location)
                    return -1;
                if (a.location > b.location)
                    return 1;
                return 0;
            }

            function compareStakeholder(a, b) {
                if (a.stakeholder < b.stakeholder)
                    return -1;
                if (a.stakeholder > b.stakeholder)
                    return 1;
                return 0;
            }

            function compareType(a, b) {
                if (a.type != "group closed" && b.type == "group closed")
                    return -1;
                if (a.type == "group closed" && b.type != "group closed")
                    return 1;
                return 0;
            }

            function compareEndDate(a, b) {
                // convert do date
                var dateA = new Date(a["end (optional)"]);
                var dateB = new Date(b["end (optional)"]);

                // compare dates
                if (isNaN(dateA.getTime()))
                    return 1;
                if (dateA.getTime() < dateB.getTime())
                    return -1;
                if (dateA.getTime() > dateB.getTime())
                    return 1;
                else
                    return 0;
            }


            function compareInitiator(a, b) {
                if (a.initiator < b.initiator)
                    return -1;
                if (a.initiator > b.initiator)
                    return 1;
                return 0;
            }


            if (this.sortBy == "name") {
                return this.listToShow.sort(compareName);
            } else if (this.sortBy == "location") {
                return this.listToShow.sort(compareLocation);
            } else if (this.sortBy == "stakeholder") {
                return this.listToShow.sort(compareStakeholder);
            } else if (this.sortBy == "city") {
                return this.listToShow.sort(compareCity);
            } else if (this.sortBy == "sortbarCol3") {
                if (this.showType == "stakeholder") {
                    return this.listToShow.sort(compareType);
                } else {
                    return this.listToShow.sort(compareEndDate)
                }
            }
            /*
            else if (this.sortBy == "sortbarCol4") {
                return this.listToShow.sort(compareCity);
            }
            */
            else {
                return this.listToShow.sort(compareID);
            }
        },

        resetBars: function () {
            // do a reset
            this.listElement1 = false;
            this.listElement2 = false;
            this.listElement3 = false;
            this.listElement4 = false;
            this.listElement5 = false;
            this.listElement6 = false;
            this.listElement7 = false;

            this.activeSort1 = true,
                this.activeSort2 = false,
                this.activeSort3 = false,
                this.activeSort4 = false,

                this.noSortItem3 = true;
            this.noSortItem4 = true;

            this.activeFilter1 = false;
            this.activeFilter2 = false;
            this.noFilter1 = true;
            this.noFilter2 = true;
            this.selectedContentView = false;

            this.sortBy = "id";

            this.noSortbar = true;
        },

        clickHandlerArticleGraph: function (event, listToShow, showType) {
            this.listToShow = listToShow;
            this.showType = showType;
            this.clickHandlerArticle(event);
        },

        // click handler
        clickHandlerArticle: function (event) {
            this.noSortbar = true;
            this.contentView = false;
            this.detailView = true;
            this.graphView = false;
            var tmpList = this.listToShow;
            var tmpItem = null;
            var tmpTypeSingle = false;
            this.detailTableClickable = false;
            this.detailAttachment = "";
            this.detailCardHeader = this.detailCardHeaderError;
            this.contentList[0] = this.detailCardBodyError;


            console.log("clicked " + event.target.id);

            // begin of html phrase
            var tmpContent = "";

            // Error case
            if (!event.target.id) {
                this.detailCardHeader = this.detailCardHeaderError;
                this.contentList[0] = this.detailCardBodyError;
                return;
            }
            // if one of the single article sidebar items like 'system'
            else if (event.target.id == "single") {
                this.noBackButton = true;

                if (this.showType == "system") {
                    tmpItem = this.jsonData.system;
                } else if (this.showType == "entrypoint") {
                    tmpItem = this.jsonData.entrypoint;
                } else {
                    tmpItem = this.jsonData.process;
                }
            }
            // still in single article view?
            else if (event.target.id == "singleArticle") {
                // then do nothing
                return;
            }
            // change to content view with the projects of the stakeholder
            else if (event.target.id == "showProjects") {
                // reset this.listToShow
                this.listToShow = this.activeProjectsData;

                // set this.showType to process
                this.showType = "processes";
                this.showGraphs = false;

                // set the sorrounding to process as well
                this.setProcessSettings();

                // call fillContent()
                this.fillContent();

                // set content view select message
                this.selectedContentView = true;

                // clear activeProjectsData
                this.activeProjectsData = [];

                return;
            }
            // change to content view with the participants of the project
            else if (event.target.id == "showParticipants") {
                // reset this.listToShow
                this.listToShow = this.participantsData;

                // set this.showType to stakeholder
                this.showType = "stakeholder";
                this.showGraphs = false;

                // set the sorrounding to stakeholder as well
                // - Sidebar to stakeholder
                // - sort/filter bar to stakeholder
                this.setStakeholderSettings();

                // call fillContent()
                this.fillContent();

                // set content view select message
                this.selectedContentView = true;

                // clear participantsData
                this.participantsData = [];

                return;
            } else {
                this.noBackButton = false;

                // search for element in data source
                // necessary cause it could be differently sorted
                for (var i = 0; i < tmpList.length; i++) {
                    if (tmpList[i].id == event.target.id) {
                        tmpItem = tmpList[i];
                        break;
                    }
                }
            }

            // fill content
            if (tmpItem != null) {
                var blockList = ["_comment", "childs", "reference (optional)", "transformation", "connection", "contact (optional)", "geoCoords (optional)", "parent", "stakeholder", "locations"];
                var show = true;

                // name or city
                if (this.showType == "locations")
                    this.detailCardHeader = tmpItem.city;
                else
                    this.detailCardHeader = tmpItem.name

                //tmpContent += `
                //<div id="singleArticle" class="card-header">` + header + `</div>
                //<div id="singleArticle" class="card-body">
                //    <table class="table">`;

                //tmpContent += `<table class="table">`;

                // fill with all the attributes
                for (item in tmpItem) {

                    // filter the detailes view
                    for (var i = 0; i < blockList.length; i++) {
                        if (blockList[i] == item) {
                            show = false;
                            break;
                        }
                    }

                    // handle special properties ---
                    // don't show if it got array structure
                    // exception for participants
                    if (Array.isArray(tmpItem[item]) & item != "participants") {;
                    }
                    // get readable ids (all)
                    else if (item == "id") {
                        var tmpList = tmpItem.id.split("/");
                        var readableID = this.capitalFirstLetter(tmpList[tmpList.length - 2]) + "/" + Number(tmpList[tmpList.length - 1]);

                        // fill
                        tmpContent += `
                                <tr>
                                    <th id="singleArticle">ID</th>
                                    <td id="singleArticle">` + readableID + `</td>
                                </tr>`;
                    }
                    // replace initiator id with name (process)
                    else if (item == "initiator") {
                        var initiatorName;

                        // search in stakeholder for id
                        for (i in this.stakeholder) {
                            if (tmpItem.initiator == this.stakeholder[i].id) {
                                // save name
                                initiatorName = this.stakeholder[i].name;
                                break;
                            }
                        }

                        // fill
                        tmpContent += `
                                <tr>
                                    <th id="singleArticle">` + this.localize(this.capitalFirstLetter(item)) + `</th>
                                    <td id="singleArticle">` + initiatorName + `</td>
                                </tr>`;
                    }
                    // replace location id with city (process)
                    else if (item == "location") {
                        var locationCity;

                        // search in locations for id
                        for (i in this.locations) {
                            if (tmpItem.location == this.locations[i].id) {
                                // save city name
                                locationCity = this.locations[i].city;
                                break;
                            }
                        }

                        // fill
                        tmpContent += `
                                <tr>
                                    <th id="singleArticle">` + this.localize(this.capitalFirstLetter(item)) + `</th>
                                    <td id="singleArticle">` + locationCity + `</td>
                                </tr>`;
                    }
                    // change color of type (stakeholder) not in the case of the three single options
                    else if (item == "type" & event != "single") {
                        var color;
                        if (tmpItem.type == "group closed")
                            color = `text-danger`
                        else
                            color = `text-success`;

                        // fill
                        tmpContent += `
                                <tr>
                                    <th id="singleArticle">` + this.localize("Type") + `</th>
                                    <td id="singleArticle" class="` + color + `">` + this.localize(tmpItem.type) + `</td>
                                </tr>`;
                    }
                    // change color of participation (process)
                    else if (item == "participation") {
                        var color;
                        if (tmpItem.participation == "closed")
                            color = `text-danger`
                        else
                            color = `text-success`;

                        // fill
                        tmpContent += `
                                <tr>
                                    <th id="singleArticle">` + this.localize("Participation") + `</th>
                                    <td id="singleArticle" class="` + color + `">` + this.localize(tmpItem.participation) + `</td>
                                </tr>`;
                    }
                    // make participants clickable, to show later the participants in a content view
                    else if (item == "participants") {

                        // enable clickable entry in detail table and reset row content
                        this.detailTableClickable = true;
                        this.detailTableClickRow = "";

                        // save data for possible click action
                        this.participantsData = [];

                        // save name of project for selected content message
                        this.selectedContentViewMessage = "Auswahl der Stakeholder des Projektes: " + tmpItem.name;

                        this.detailTableClickRow += `
                                    <th id="showParticipants" class="text-black">` + this.localize(this.capitalFirstLetter(item)) + `</th>
                                    <td id="showParticipants"  data-toggle="tooltip" title="Auswahl der Stakeholder des Projektes anzeigen">`;

                        // go through stakeholder and compare
                        for (stakeItem in this.stakeholder) {
                            for (participantsItem in tmpItem[item]) {
                                if (this.stakeholder[stakeItem].id == tmpItem[item][participantsItem]) {
                                    this.detailTableClickRow += `<li id="showParticipants"><span id="showParticipants" class="text-primary">` + this.stakeholder[stakeItem].name + "</span></li>";

                                    // save to this.participantsData to later show a content view (with a click)
                                    this.participantsData.push(this.stakeholder[stakeItem]);
                                }
                            }
                        }

                        this.detailTableClickRow += `
                                    </td>`;

                        // handle case of no participants
                        if (this.participantsData.length <= 0) {
                            this.detailTableClickable = false;
                            this.detailTableClickRow = "";
                        }
                    }
                    // get readable time
                    else if (item == "start" || item == "created" || item == "modified" || item == "end (optional)") {

                        // error fill
                        if (!tmpItem[item]) {
                            tmpContent += `
                            <tr>
                                <th id="singleArticle">` + this.localize(this.capitalFirstLetter(item)) + `</th>
                                <td id="singleArticle">` + "" + `</td>
                            </tr>`;
                        } else {
                            var tmpDate = new Date(tmpItem[item]);

                            readableDate = (tmpDate.getDate() + "").padStart(2, "0") + "." + (tmpDate.getMonth() + 1 + "").padStart(2, "0") + "." + tmpDate.getFullYear() + " (" + this.days[tmpDate.getDay()] + ")<br>" +
                                tmpDate.getHours() + ":" + tmpDate.getMinutes() + " Uhr " + "(UTC" + (tmpDate.getTimezoneOffset() / 60) + ")";

                            // fill
                            tmpContent += `
                            <tr>
                                <th id="singleArticle">` + this.localize(this.capitalFirstLetter(item)) + `</th>
                                <td id="singleArticle">` + readableDate + `</td>
                            </tr>`;
                        }
                    }
                    // show the rest normaly
                    else if (show) {

                        tmpContent += `
                                <tr>
                                    <th id="singleArticle">` + this.localize(this.capitalFirstLetter(item)) + `</th>
                                    <td id="singleArticle">` + tmpItem[item] + `</td>
                                </tr>`;
                    }

                    show = true;
                }

                // check for stakeholder detail view
                // Add Amount of Projects that he is included in
                if (this.showType == "stakeholder") {
                    // enable clickable entry in detail table and reset row content
                    this.detailTableClickable = true;
                    this.detailTableClickRow = "";

                    var projectCounter = 0;
                    var activeProjectCounter = 0;
                    var workingProjects = [];

                    // save name of project for selected content message
                    this.selectedContentViewMessage = "Auswahl der Projekte des Stakeholder: " + tmpItem.name;

                    // get current date
                    var currentDate = new Date();
                    var itemDate;

                    for (item in this.children) {
                        for (subitem in this.children[item].participants) {
                            // is the stakeholder included ?
                            if (this.children[item].participants[subitem] == tmpItem.id) {
                                projectCounter++;

                                // check if project is still running
                                itemDate = new Date(this.children[item]["end (optional)"]);

                                if (isNaN(itemDate.getTime()) | itemDate.getTime() > currentDate.getTime()) {
                                    activeProjectCounter++;
                                    // save name of project in list
                                    workingProjects.push(this.children[item].name);

                                    // save whole project information for the possibility of clicking on the list and get to the content view
                                    this.activeProjectsData.push(this.children[item]);
                                }
                                break;
                            }
                        }
                    }

                    // fill content
                    tmpContent += `
                    <tr>
                        <th id="singleArticle">Anzahl der Projekte</th>
                        <td id="singleArticle">` + projectCounter;

                    // fill project-list with working projects if they got one, otherwise don't show that line
                    if (projectCounter > 0) {
                        tmpContent += `
                        </td>
                    </tr>`;

                        this.detailTableClickRow = `
                        <th id="showProjects" class="text-black">Aktive Projekte</th>
                        <td id="showProjects" data-toggle="tooltip" title="Auswahl der Projekte des Stakeholders anzeigen">`;

                        for (item in workingProjects) {
                            this.detailTableClickRow += `<li id="showProjects"><span  id="showProjects" class="text-primary">` + workingProjects[item] + "</span></li>";
                        }
                    }

                    this.detailTableClickRow += `
                        </td>`;

                    // handle case of no participants
                    if (this.activeProjectsData.length <= 0) {
                        this.detailTableClickable = false;
                        this.detailTableClickRow = "";
                    }
                }


                // close table div
                //tmpContent += `</div>`;
                // search for pictures or pdf
                if (this.attachments[event.target.id]) {
                    this.detailAttachment = "<h5>Anhang</h5>";
                    attachment = this.attachments[event.target.id];
                    if (attachment.endsWith(".pdf")) {
                        this.detailAttachment += "<embed src='Anlagen/" + attachment + "' class='w-100' height='500px' type='application/pdf'>";

                    } else {
                        this.detailAttachment += "<div class='text-center'><img src='Anlagen/" + attachment + "' class='img-fluid'></div>";
                    }
                } else {
                    this.detailAttachment = "";
                }
                //console.log("Something was found at " + event.target.id);
            } else {
                console.log("Nothing was found at " + event.target.id);
            }

            // end of html phrase
            //tmpContent += `</div>`;


            // set content as item in the contentList
            this.contentList = [];
            this.contentList.push(tmpContent);
        },

        clickHandlerSidebar: function (event) {
            this.resetBars();
            this.contentView = false;
            this.detailView = false;
            this.graphView = false;
            this.showGraphs = false;

            // set showType and sidebar item active
            if (event.target.id == "sidebarLocations") {
                this.listElement2 = true;
                this.showType = "locations";
                this.sortLabel2 = "Stadt";
            } else if (event.target.id == "sidebarStakeholder") {
                this.setStakeholderSettings();
            } else if (event.target.id == "sidebarSystem") {
                this.listElement4 = true;
                this.showType = "system";
            } else if (event.target.id == "sidebarEntrypoint") {
                this.listElement5 = true;
                this.showType = "entrypoint";
            } else if (event.target.id == "sidebarMainprocess") {
                this.listElement6 = true;
                this.showType = "mainprocess";
            } else if (event.target.id == "sidebarStatistics") {
                this.listElement7 = true;
                this.graphView = true;
                this.showGraphs = true;
                this.showType = "statistics";
            } else {
                this.setProcessSettings();
            }
            // set the data source for the content
            this.setDefaultListToShow();
            if (this.listElement7) {
                // graph
                this.graphView = true;
            } else if (this.listElement4 | this.listElement5 | this.listElement6) {
                this.clickHandlerArticle({
                    target: {
                        id: "single"
                    }
                });
            } else {
                // fill the content space
                this.fillContent();
            }
        },

        clickHandlerSortbar: function (event) {
            // do a reset
            this.activeSort1 = false;
            this.activeSort2 = false;
            this.activeSort3 = false;
            this.activeSort4 = false;

            if (event.target.id == "sortbarCol2") {
                this.activeSort2 = true;
                this.sortBy = "name";

                // special case - shouldn't be so
                if (this.showType == "locations") {
                    this.sortBy = "city";
                }
            } else if (event.target.id == "sortbarCol3") {
                this.activeSort3 = true;
                this.sortBy = "sortbarCol3";
            } else if (event.target.id == "sortbarCol4") {
                this.activeSort4 = true;
                this.sortBy = "sortbarCol4";
            } else {
                this.activeSort1 = true;
                this.sortBy = "id";
            }

            // show new sorted CURRENT content
            // nothing should happen in the single article view
            if (this.showType != "singleArticle") {
                this.fillContent();
            }
        },

        clickHandlerFilter: function (event) {
            if (event.target.id == "filter1") {
                if (this.activeFilter1) {
                    this.activeFilter1 = false;

                    // get old item back into list
                    for (item in this.outtakenFilter1) {
                        this.listToShow.push(this.outtakenFilter1[item]);
                    }
                    // reset list
                    this.outtakenFilter1 = [];
                } else {
                    this.activeFilter1 = true;

                    // build new listToShow
                    if (this.showType == "processes") {
                        var tmpList = [];
                        for (item in this.listToShow) {
                            if (this.listToShow[item].participation != "closed")
                                tmpList.push(this.listToShow[item]);
                            else {
                                this.outtakenFilter1.push(this.listToShow[item]);
                            }
                        }
                    }

                    // build new listToShow
                    if (this.showType == "stakeholder") {
                        var tmpList = [];
                        for (item in this.listToShow) {
                            if (this.listToShow[item].type != "group closed")
                                tmpList.push(this.listToShow[item]);
                            else {
                                this.outtakenFilter1.push(this.listToShow[item]);
                            }
                        }
                    }
                    this.listToShow = tmpList;
                }

            }

            if (event.target.id == "filter2") {
                if (this.activeFilter2) {
                    this.activeFilter2 = false;

                    // get old item back into list
                    //this.listToShow.concat(this.outtakenFilter2);
                    for (item in this.outtakenFilter2) {
                        this.listToShow.push(this.outtakenFilter2[item]);
                    }
                    // reset list
                    this.outtakenFilter2 = [];
                } else {
                    this.activeFilter2 = true;

                    // build new listToShow
                    if (this.showType == "processes") {
                        var tmpList = [];

                        // get current date
                        var currentDate = new Date();
                        var itemDate;

                        for (item in this.listToShow) {
                            itemDate = new Date(this.listToShow[item]["end (optional)"]);

                            if (isNaN(itemDate.getTime()) | itemDate.getTime() > currentDate.getTime()) {
                                tmpList.push(this.listToShow[item]);
                            } else {
                                this.outtakenFilter2.push(this.listToShow[item]);
                            }

                        }
                    }
                    this.listToShow = tmpList;
                }
            }
            // show new content
            this.fillContent();
        },

        capitalFirstLetter: function (string) {
            return string.charAt(0).toUpperCase() + string.slice(1);
        },

        localize: function (string) {
            // translate text by replacing strings
            string = string.replace("Description", "Beschreibung");
            string = string.replace("Start", "Anfang");
            string = string.replace("End (optional)", "Ende (optional)");
            string = string.replace("Created", "Erstellt");
            string = string.replace("Modified", "Verändert");
            string = string.replace("Participation", "Mitwirkung");
            string = string.replace("Participants", "Stakeholder");
            string = string.replace("Address", "Adresse");
            string = string.replace("Zip", "PLZ");
            string = string.replace("City", "Stadt");
            string = string.replace("Room (optional)", "Raum (optional)");
            string = string.replace("Type", "Status");
            string = string.replace("group closed", "geschlossen");
            // someone can't write opened...
            string = string.replace("group openend", "offen");
            string = string.replace("group opened", "offen");
            string = string.replace("group opend", "offen");
            string = string.replace("partial opened", "teilweise offen");
            string = string.replace("closed", "geschlossen");
            return string;
        },

        drawGraphs() {
            this.graphProcessNames = [];
            this.graphProcessData = [];
            this.graphStakeholderNames = [];
            this.graphStakeholderData = [];
            // prepare process information for graph
            for (process in this.children) {
                // get short name
                var shortName;
                if (this.children[process].name.length > 25) {
                    shortName = this.children[process].name.substr(0, 22) + "...";
                } else {
                    shortName = this.children[process].name;
                }
                // add processes (x-axis)
                this.graphProcessNames.push({
                    category: this.children[process].name,
                    short: shortName,
                    link: this.children[process].id
                });
                // add process date ranges (y-axis)
                var startDate = Date.parse(this.children[process]["start"]);
                var endDate = Date.now();
                // optional (unused): finished processes in different color
                if (this.children[process]["end (optional)"]) {
                    endDate = Date.parse(this.children[process]["end (optional)"]);
                    this.graphProcessData.push({
                        low: startDate,
                        high: endDate,
                        // states: {
                        //     hover: {
                        //         color: "green"
                        //     }
                        // },
                        // color: "lightblue"
                    })
                } else {
                    this.graphProcessData.push({
                        low: startDate,
                        high: endDate
                    })
                }
            };
            // prepare stakeholder information for graph
            var projectCounter;
            for (stakeholder in this.stakeholder) {
                // count projects
                projectCounter = 0;
                for (item in this.children) {
                    for (subitem in this.children[item].participants) {
                        if (this.children[item].participants[subitem] == this.stakeholder[stakeholder].id) {
                            projectCounter++;
                            break;
                        }
                    }
                }
                // add project count (x-axis)
                this.graphStakeholderData.push(projectCounter)

                // add stakeholder information (y-axis)
                this.graphStakeholderNames.push({
                    category: this.stakeholder[stakeholder].name,
                    link: this.stakeholder[stakeholder].id
                });
            }
            // draw both graphs
            this.drawProcessesGraph();
            this.drawStakeholderGraph();
        },

        drawProcessesGraph() {
            // draw process graph into element with id processGraph
            Highcharts.chart('processGraph', {
                chart: {
                    type: 'columnrange',
                    inverted: true
                },
                title: {
                    text: 'Fortschritt der Prozesse'
                },
                xAxis: {
                    categories: this.graphProcessNames,
                    // labels: {
                    //     enabled: false
                    // },
                    labels: {
                        formatter: function () {
                            return this.value.short;
                        },
                    },
                    visible: false
                },
                yAxis: {
                    type: 'datetime',
                    title: {
                        text: ''
                    },
                    startOnTick: false,
                    endOnTick: false
                },
                plotOptions: {
                    series: {
                        cursor: 'pointer',
                        animation: false,
                        point: {
                            events: {
                                click: function () {
                                    vue.clickHandlerArticleGraph({
                                        target: {
                                            id: this.category.link
                                        }
                                    }, vue.children, "process");
                                }
                            }
                        },
                        pointWidth: 9
                    }
                },
                tooltip: {
                    headerFormat: '<b> {point.key.category} </b> <br > ',
                    pointFormat: '{point.low:%d.%m.%Y} bis {point.high:%d.%m.%Y}',
                },
                legend: {
                    enabled: false
                },
                series: [{
                    name: 'Prozess',
                    data: this.graphProcessData
                }]
            });
        },

        drawStakeholderGraph() {
            // draw stakeholder graph in element with id stakeholderGraph
            Highcharts.chart('stakeholderGraph', {
                chart: {
                    type: 'bar'
                },
                title: {
                    text: 'Prozesse pro Stakeholder'
                },
                xAxis: {
                    categories: this.graphStakeholderNames,
                    //visible: false,
                    labels: {
                        formatter: function () {
                            return this.value.category;
                        },
                    }
                },
                yAxis: {
                    type: 'number',
                    allowDecimals: false,
                    title: {
                        text: ''
                    }
                },
                plotOptions: {
                    series: {
                        cursor: 'pointer',
                        animation: false,
                        minPointLength: 5,
                        point: {
                            events: {
                                click: function () {
                                    vue.clickHandlerArticleGraph({
                                        target: {
                                            id: this.category.link
                                        }
                                    }, vue.stakeholder, "stakeholder");
                                }
                            }
                        }
                    }
                },
                tooltip: {
                    headerFormat: '<b> {point.key.category} </b><br>',
                    pointFormat: 'wirkt an {point.y} Prozessen mit.',
                },
                legend: {
                    enabled: false
                },
                series: [{
                    name: 'Stakeholder',
                    data: this.graphStakeholderData
                }]
            });
        }
    },

    // function called in the beginning
    mounted() {

        // get json stuff
        var self = this;
        $.getJSON("data/process.json", function (data) {
            // read in data
            self.jsonData = data;
            self.children = self.jsonData.process.childs;
            self.locations = self.jsonData.process.locations;
            self.stakeholder = self.jsonData.process.stakeholder;

            console.log("reading of json file was successfull");

            // init
            self.listToShow = self.children;

            // fill with content
            self.fillContent();
        });
    },

})