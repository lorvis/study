 function ajaxTreeRepr(obj_id) {
        var elem = document.getElementById("tree-repr");
        var new_elem = document.createElement("div");

        new_elem.innerHTML = makeRequest("{{ url_for("ajax_repr", id=obj_id) }}");
        elem.parentNode.replaceChild(new_elem, elem);
    }

    function makeRequest(url) {
        var httpRequest = new XMLHttpRequest();

        if (!httpRequest) {
            alert("Can't create XMLHTTP");
            return false;
        }

        httpRequest.open("GET", url);
        httpRequest.send();

        return httpRequest.responseText
    }