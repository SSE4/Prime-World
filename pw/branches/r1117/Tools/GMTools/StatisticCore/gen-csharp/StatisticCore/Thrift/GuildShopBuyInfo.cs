/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using Thrift;
using Thrift.Collections;
using System.Runtime.Serialization;
using Thrift.Protocol;
using Thrift.Transport;

namespace StatisticCore.Thrift
{

  #if !SILVERLIGHT
  [Serializable]
  #endif
  public partial class GuildShopBuyInfo : TBase
  {
    private long _auid;
    private long _guildid;
    private bool _hassuzerain;
    private int _shoplevel;
    private int _shopitemid;
    private ResourceTable _rchange;
    private ResourceTable _rtotal;
    private int _guildpointschange;
    private int _guildpointstotal;
    private int _timestamp;

    public long Auid
    {
      get
      {
        return _auid;
      }
      set
      {
        __isset.auid = true;
        this._auid = value;
      }
    }

    public long Guildid
    {
      get
      {
        return _guildid;
      }
      set
      {
        __isset.guildid = true;
        this._guildid = value;
      }
    }

    public bool Hassuzerain
    {
      get
      {
        return _hassuzerain;
      }
      set
      {
        __isset.hassuzerain = true;
        this._hassuzerain = value;
      }
    }

    public int Shoplevel
    {
      get
      {
        return _shoplevel;
      }
      set
      {
        __isset.shoplevel = true;
        this._shoplevel = value;
      }
    }

    public int Shopitemid
    {
      get
      {
        return _shopitemid;
      }
      set
      {
        __isset.shopitemid = true;
        this._shopitemid = value;
      }
    }

    public ResourceTable Rchange
    {
      get
      {
        return _rchange;
      }
      set
      {
        __isset.rchange = true;
        this._rchange = value;
      }
    }

    public ResourceTable Rtotal
    {
      get
      {
        return _rtotal;
      }
      set
      {
        __isset.rtotal = true;
        this._rtotal = value;
      }
    }

    public int Guildpointschange
    {
      get
      {
        return _guildpointschange;
      }
      set
      {
        __isset.guildpointschange = true;
        this._guildpointschange = value;
      }
    }

    public int Guildpointstotal
    {
      get
      {
        return _guildpointstotal;
      }
      set
      {
        __isset.guildpointstotal = true;
        this._guildpointstotal = value;
      }
    }

    public int Timestamp
    {
      get
      {
        return _timestamp;
      }
      set
      {
        __isset.timestamp = true;
        this._timestamp = value;
      }
    }


    public Isset __isset;
    #if !SILVERLIGHT
    [Serializable]
    #endif
    public struct Isset {
      public bool auid;
      public bool guildid;
      public bool hassuzerain;
      public bool shoplevel;
      public bool shopitemid;
      public bool rchange;
      public bool rtotal;
      public bool guildpointschange;
      public bool guildpointstotal;
      public bool timestamp;
    }

    public GuildShopBuyInfo() {
    }

    public void Read (TProtocol iprot)
    {
      TField field;
      iprot.ReadStructBegin();
      while (true)
      {
        field = iprot.ReadFieldBegin();
        if (field.Type == TType.Stop) { 
          break;
        }
        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.I64) {
              Auid = iprot.ReadI64();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 2:
            if (field.Type == TType.I64) {
              Guildid = iprot.ReadI64();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 3:
            if (field.Type == TType.Bool) {
              Hassuzerain = iprot.ReadBool();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 4:
            if (field.Type == TType.I32) {
              Shoplevel = iprot.ReadI32();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 5:
            if (field.Type == TType.I32) {
              Shopitemid = iprot.ReadI32();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 6:
            if (field.Type == TType.Struct) {
              Rchange = new ResourceTable();
              Rchange.Read(iprot);
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 7:
            if (field.Type == TType.Struct) {
              Rtotal = new ResourceTable();
              Rtotal.Read(iprot);
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 8:
            if (field.Type == TType.I32) {
              Guildpointschange = iprot.ReadI32();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 9:
            if (field.Type == TType.I32) {
              Guildpointstotal = iprot.ReadI32();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          case 10:
            if (field.Type == TType.I32) {
              Timestamp = iprot.ReadI32();
            } else { 
              TProtocolUtil.Skip(iprot, field.Type);
            }
            break;
          default: 
            TProtocolUtil.Skip(iprot, field.Type);
            break;
        }
        iprot.ReadFieldEnd();
      }
      iprot.ReadStructEnd();
    }

    public void Write(TProtocol oprot) {
      TStruct struc = new TStruct("GuildShopBuyInfo");
      oprot.WriteStructBegin(struc);
      TField field = new TField();
      if (__isset.auid) {
        field.Name = "auid";
        field.Type = TType.I64;
        field.ID = 1;
        oprot.WriteFieldBegin(field);
        oprot.WriteI64(Auid);
        oprot.WriteFieldEnd();
      }
      if (__isset.guildid) {
        field.Name = "guildid";
        field.Type = TType.I64;
        field.ID = 2;
        oprot.WriteFieldBegin(field);
        oprot.WriteI64(Guildid);
        oprot.WriteFieldEnd();
      }
      if (__isset.hassuzerain) {
        field.Name = "hassuzerain";
        field.Type = TType.Bool;
        field.ID = 3;
        oprot.WriteFieldBegin(field);
        oprot.WriteBool(Hassuzerain);
        oprot.WriteFieldEnd();
      }
      if (__isset.shoplevel) {
        field.Name = "shoplevel";
        field.Type = TType.I32;
        field.ID = 4;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32(Shoplevel);
        oprot.WriteFieldEnd();
      }
      if (__isset.shopitemid) {
        field.Name = "shopitemid";
        field.Type = TType.I32;
        field.ID = 5;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32(Shopitemid);
        oprot.WriteFieldEnd();
      }
      if (Rchange != null && __isset.rchange) {
        field.Name = "rchange";
        field.Type = TType.Struct;
        field.ID = 6;
        oprot.WriteFieldBegin(field);
        Rchange.Write(oprot);
        oprot.WriteFieldEnd();
      }
      if (Rtotal != null && __isset.rtotal) {
        field.Name = "rtotal";
        field.Type = TType.Struct;
        field.ID = 7;
        oprot.WriteFieldBegin(field);
        Rtotal.Write(oprot);
        oprot.WriteFieldEnd();
      }
      if (__isset.guildpointschange) {
        field.Name = "guildpointschange";
        field.Type = TType.I32;
        field.ID = 8;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32(Guildpointschange);
        oprot.WriteFieldEnd();
      }
      if (__isset.guildpointstotal) {
        field.Name = "guildpointstotal";
        field.Type = TType.I32;
        field.ID = 9;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32(Guildpointstotal);
        oprot.WriteFieldEnd();
      }
      if (__isset.timestamp) {
        field.Name = "timestamp";
        field.Type = TType.I32;
        field.ID = 10;
        oprot.WriteFieldBegin(field);
        oprot.WriteI32(Timestamp);
        oprot.WriteFieldEnd();
      }
      oprot.WriteFieldStop();
      oprot.WriteStructEnd();
    }

    public override string ToString() {
      StringBuilder sb = new StringBuilder("GuildShopBuyInfo(");
      sb.Append("Auid: ");
      sb.Append(Auid);
      sb.Append(",Guildid: ");
      sb.Append(Guildid);
      sb.Append(",Hassuzerain: ");
      sb.Append(Hassuzerain);
      sb.Append(",Shoplevel: ");
      sb.Append(Shoplevel);
      sb.Append(",Shopitemid: ");
      sb.Append(Shopitemid);
      sb.Append(",Rchange: ");
      sb.Append(Rchange== null ? "<null>" : Rchange.ToString());
      sb.Append(",Rtotal: ");
      sb.Append(Rtotal== null ? "<null>" : Rtotal.ToString());
      sb.Append(",Guildpointschange: ");
      sb.Append(Guildpointschange);
      sb.Append(",Guildpointstotal: ");
      sb.Append(Guildpointstotal);
      sb.Append(",Timestamp: ");
      sb.Append(Timestamp);
      sb.Append(")");
      return sb.ToString();
    }

  }

}
