// Copyright 2010, Camilo Aguilar. Cloudescape, LLC.
#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include "node_libvirt.h"

#include "worker.h"
#include "worker_macros.h"

namespace NodeLibvirt {

class Network : public ObjectWrap
{
public:
  static void Initialize();
  static Local<Object> NewInstance(const LibVirtHandle &handle);
  virtual ~Network();

private:
  explicit Network(virNetworkPtr handle) : handle_(handle) {}
  static Persistent<FunctionTemplate> constructor_template;
  virNetworkPtr handle_;

  friend class Hypervisor;

protected:
  // HYPERVISOR METHODS
  static NAN_METHOD(LookupByName);
  static NAN_METHOD(LookupByUUID);
  static NAN_METHOD(Define);
  static NAN_METHOD(Create);

  // ACTIONS
  static NAN_METHOD(Destroy);
  static NAN_METHOD(Start);
  static NAN_METHOD(Undefine);

  // ACCESSORS/MUTATORS
  static NAN_METHOD(GetName);
  static NAN_METHOD(GetUUID);
  static NAN_METHOD(GetAutostart);
  static NAN_METHOD(SetAutostart);
  static NAN_METHOD(GetBridgeName);
  static NAN_METHOD(IsActive);
  static NAN_METHOD(IsPersistent);
  static NAN_METHOD(ToXml);

private:
  // HYPERVISOR METHOD WORKERS
  NLV_LOOKUP_BY_VALUE_WORKER(Network, LookupByName);
  NLV_LOOKUP_BY_VALUE_WORKER(Network, LookupByUUID);
  NLV_LOOKUP_BY_VALUE_WORKER(Network, Define);
  NLV_LOOKUP_BY_VALUE_WORKER(Network, Create);

  // METHOD WORKERS
  NLV_PRIMITIVE_RETURN_WORKER(Destroy, virNetworkPtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER(Start, virNetworkPtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER(Undefine, virNetworkPtr, bool);

  // ACCESSORS/MUTATORS WORKERS
  NLV_PRIMITIVE_RETURN_WORKER(GetName, virNetworkPtr, std::string);
  NLV_PRIMITIVE_RETURN_WORKER(GetUUID, virNetworkPtr, std::string);
  NLV_PRIMITIVE_RETURN_WORKER(GetAutostart, virNetworkPtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER(GetBridgeName, virNetworkPtr, std::string);
  NLV_PRIMITIVE_RETURN_WORKER(IsActive, virNetworkPtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER(IsPersistent, virNetworkPtr, bool);
  NLV_PRIMITIVE_RETURN_WORKER(ToXml, virNetworkPtr, std::string);

  class SetAutostartWorker : public PrimitiveReturnWorker<bool> {
  public:
    SetAutostartWorker(NanCallback *callback, virNetworkPtr handle, bool autoStart)
      : PrimitiveReturnWorker<bool>(callback, handle), autoStart_(autoStart) {} \
    void Execute();
  private:
    bool autoStart_;
  };

};

}  // namespace NodeLibvirt

#endif  // SRC_NETWORK_H_

