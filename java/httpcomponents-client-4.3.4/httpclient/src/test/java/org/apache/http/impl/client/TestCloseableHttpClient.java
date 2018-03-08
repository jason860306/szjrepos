/*
 * ====================================================================
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 */
package org.apache.http.impl.client;

import java.io.IOException;
import java.io.InputStream;

import org.apache.http.HttpEntity;
import org.apache.http.HttpHost;
import org.apache.http.HttpRequest;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.protocol.HttpContext;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

/**
 *  Simple tests for {@link CloseableHttpClient}.
 */
public class TestCloseableHttpClient {

    static abstract class NoopCloseableHttpClient extends CloseableHttpClient {

        @Override
        protected CloseableHttpResponse doExecute(
                final HttpHost target,
                final HttpRequest request,
                final HttpContext context) throws IOException, ClientProtocolException {
            return null;
        }

    }

    private NoopCloseableHttpClient client;
    private InputStream content;
    private HttpEntity entity;
    private CloseableHttpResponse response;

    @Before
    public void setup() throws Exception {
        content = Mockito.mock(InputStream.class);
        entity = Mockito.mock(HttpEntity.class);
        response = Mockito.mock(CloseableHttpResponse.class);
        Mockito.when(entity.getContent()).thenReturn(content);
        Mockito.when(entity.isStreaming()).thenReturn(Boolean.TRUE);
        Mockito.when(response.getEntity()).thenReturn(entity);
        client = Mockito.mock(NoopCloseableHttpClient.class, Mockito.CALLS_REAL_METHODS);
    }

    @Test
    public void testExecuteRequestAbsoluteURI() throws Exception {
        final HttpGet httpget = new HttpGet("https://somehost:444/stuff");
        client.execute(httpget);

        Mockito.verify(client).doExecute(
                Mockito.eq(new HttpHost("somehost", 444, "https")),
                Mockito.same(httpget),
                (HttpContext) Mockito.isNull());
    }

    @Test
    public void testExecuteRequestRelativeURI() throws Exception {
        final HttpGet httpget = new HttpGet("/stuff");
        client.execute(httpget);

        Mockito.verify(client).doExecute(
                (HttpHost) Mockito.isNull(),
                Mockito.same(httpget),
                (HttpContext) Mockito.isNull());
    }

    @Test
    public void testExecuteRequestInvalidHost() throws Exception {
        final HttpGet httpget = new HttpGet("http://_/stuff");
        client.execute(httpget);

        Mockito.verify(client).doExecute(
                Mockito.eq(new HttpHost("_", -1, "http")),
                Mockito.same(httpget),
                (HttpContext) Mockito.isNull());
    }

    @Test(expected=ClientProtocolException.class)
    public void testExecuteRequestInvalidHost2() throws Exception {
        final HttpGet httpget = new HttpGet("http://@/stuff");
        client.execute(httpget);
    }

    @Test
    public void testExecuteRequest() throws Exception {
        final HttpGet httpget = new HttpGet("https://somehost:444/stuff");

        Mockito.when(client.doExecute(
                new HttpHost("somehost", 444, "https"), httpget, null)).thenReturn(response);

        final CloseableHttpResponse result = client.execute(httpget);
        Assert.assertSame(response, result);
    }

    @Test
    @SuppressWarnings("unchecked")
    public void testExecuteRequestHandleResponse() throws Exception {
        final HttpGet httpget = new HttpGet("https://somehost:444/stuff");

        Mockito.when(client.doExecute(
                new HttpHost("somehost", 444, "https"), httpget, null)).thenReturn(response);

        final ResponseHandler<HttpResponse> handler = Mockito.mock(ResponseHandler.class);

        client.execute(httpget, handler);

        Mockito.verify(client).doExecute(
                Mockito.eq(new HttpHost("somehost", 444, "https")),
                Mockito.same(httpget),
                (HttpContext) Mockito.isNull());
        Mockito.verify(handler).handleResponse(response);
        Mockito.verify(content).close();
    }

    @Test(expected=IOException.class)
    @SuppressWarnings("unchecked")
    public void testExecuteRequestHandleResponseIOException() throws Exception {
        final HttpGet httpget = new HttpGet("https://somehost:444/stuff");

        Mockito.when(client.doExecute(
                new HttpHost("somehost", 444, "https"), httpget, null)).thenReturn(response);

        final ResponseHandler<HttpResponse> handler = Mockito.mock(ResponseHandler.class);

        Mockito.when(handler.handleResponse(response)).thenThrow(new IOException());

        try {
            client.execute(httpget, handler);
        } catch (final IOException ex) {
            Mockito.verify(client).doExecute(
                    Mockito.eq(new HttpHost("somehost", 444, "https")),
                    Mockito.same(httpget),
                    (HttpContext) Mockito.isNull());
            Mockito.verify(content).close();
            throw ex;
        }
    }

    @Test(expected=RuntimeException.class)
    @SuppressWarnings("unchecked")
    public void testExecuteRequestHandleResponseHttpException() throws Exception {
        final HttpGet httpget = new HttpGet("https://somehost:444/stuff");

        Mockito.when(client.doExecute(
                new HttpHost("somehost", 444, "https"), httpget, null)).thenReturn(response);

        final ResponseHandler<HttpResponse> handler = Mockito.mock(ResponseHandler.class);

        Mockito.when(handler.handleResponse(response)).thenThrow(new RuntimeException());

        try {
            client.execute(httpget, handler);
        } catch (final RuntimeException ex) {
            Mockito.verify(client).doExecute(
                    Mockito.eq(new HttpHost("somehost", 444, "https")),
                    Mockito.same(httpget),
                    (HttpContext) Mockito.isNull());
            Mockito.verify(content).close();
            throw ex;
        }
    }

}
