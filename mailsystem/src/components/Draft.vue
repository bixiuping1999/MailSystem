<template>
    <div class="sendmail_frame" ref="main_frame">
    <form >
        
        <ul class="nav nav-pills">
            <li role="presentation" class="left"><button type="button" class="btn btn-primary" @click="sendMail($event)">发送</button></li>
            <li role="presentation" class="left"><button type="button" class="btn btn-info" @click="saveDraft">保存</button></li>
            <li role="presentation" class="right"><button type="button" class="btn btn-danger" @click="deleteDraft">
                <span class="glyphicon glyphicon-trash" aria-hidden="true"></span></button>
            </li>
        </ul>
        <div class="cutoff_line"></div>
        <div class="input-group recive">
            <span class="input-group-addon" id="basic-addon3" >收件人</span>
            <input type="email" class="form-control" aria-describedby="basic-addon3" v-model="draftMail.recipient" name="recver">
        </div>
        <div class="mail_group">
            <div class="input-group">
                <span class="input-group-addon " id="basic-addon">主题</span>               
                <input type="text" class="form-control" id="basic-url" aria-describedby="basic-addon" v-model="draftMail.theme" name="theme">
               
                               
            </div>
            <div class="form-group">
                <input type="file" id="thisfile" ref="inputFile" style="display:none" @change="fileChange($event)" name="attachment">
                <input type="text" style="display:none" @change="fileChange" name="id" v-model="userid">
                <div id="uplode_group" class="uplode">
                    <button class="btn btn-info mybtn" id="input_display" @click="uploadFile" type="button">
                        <span class="glyphicon glyphicon-folder-open myspan" aria-hidden="true"></span>上传附件
                    </button>
                    
                    <input type="text" name="" id="filePath" disabled v-model="fileName">
                </div>
                <textarea class="form-control" rows="22" v-model="draftMail.content" name="content"></textarea>
           </div>
        </div>

    </form>
    </div>
</template>
<style scoped>
    .sendmail_frame{
        position: relative;
        height: 99%;
        top: 1%;
        left: 1%;
        width: 95%;
        background-color: rgba(73, 71, 67, 0.5);
        border-radius: 2%;
    }
    ul{
        position: relative;
        top: 0%;
        margin: 1%;
        width: 100%;

    }
    .left{
       position: relative;
       margin-right: 2%;

    }
    .right{
        position: absolute;
        right: 2%;
    }
    .cutoff_line{
        width: 100%;
        height: 1px;
        background-color: blue;
    }
    .recive{
        position: relative;
        margin-top: 1%;
        margin-left: 1%;
        width: 98%;
    }
    .inputfile_label{
        position: relative;
        margin: 1%;
        float: left;
    }
    .mail_group{
        position: relative;
        margin: 1%;
    }

    .inputfile_label{
        position: relative;
        float: left;
    }

    .uplode{
        position: relative;
        margin-top: 1%;
        margin-bottom: 1%;
    }
    .uplode input{
        position: relative;

        margin-bottom: 0%;
    }
    .mybtn{
        position: relative;
        vertical-align: middle;
    }
    .myspan{
        position: relative;
        margin: 2px;
    }
    

</style>
<script>
import savedraftutil from '../utils/saveDraftUtil'
import Axios from 'axios'
import Vue from 'vue'
import qs from 'querystring'
Axios.defaults.headers.post['Content-Type']='multipart/form-data'

Vue.prototype.$http = Axios
Vue.prototype.$axios=Axios
export default {
    data(){
        return {
            flag:false,
            fileName:'',
            file:'',
            draftMail:savedraftutil.readData('draft_mail'),
            userid:''
        }
    },
    methods:{
        uploadFile:function(){
            this.$refs.inputFile.dispatchEvent(new MouseEvent('click'))
            
        },
        fileChange:function(e){
            this.fileName=this.$refs.inputFile.files[0].name
            this.file=e.target.files[0]
            console.log(this.file)
        },
        refresh:function(){
            this.$router.go(0)
        },
        deleteDraft:function(){
            savedraftutil.deleteData('draft_mail')
            this.refresh()
            alert('删除草稿')
        },
        saveDraft(){
            if(this.fileName!=''){
                this.draftMail.attachmentName=this.fileName
                this.draftMail.attachment=this.$refs.inputFile.files[0]
            }
            savedraftutil.saveData('draft_mail',this.draftMail)
            console.log(this.draftMail)
            alert('保存成功')
        },
        sendMail:function(event){
            event.preventDefault()
            if(this.draftMail.recipient==''){
                alert('请输入收件人邮箱')
            }else{
                
                let formData = new FormData()
                let userid = savedraftutil.readData('userid')
                formData.append("id",userid)
                const self = this
                formData.append("attachment",this.file)           
                formData.append("recver",this.draftMail.recipient)
                formData.append("content",this.draftMail.content)
                formData.append("theme",this.draftMail.theme)
                console.log(this.draftMail.recipient)
                let config={
                    headers:{
                        'Content-Type':'multipart/form-data'
                    }
                }
                const url = "http://127.0.0.1:8006/send_mail_with_attach"
                this.$axios.post(url,formData,config).then(function(res){
                    console.log(res)
                    if(res.status==200){
                        console.log("success send")
                        alert("发送成功")
                        self.refresh()
                    }
                })
            }
            


        }               
    },
    mounted(){
        if(this.draftMail===undefined ){
            this.draftMail={recipient:'1',theme:'',attachment:Object,attachmentName:'',content:''}
        }
        if(this.draftMail.attachmentName!=''){
            this.fileName=this.draftMail.attachmentName
        }
        
    }
}
</script>
